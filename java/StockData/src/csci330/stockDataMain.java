package csci330;

import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;
import java.util.Map.Entry;

/**
 * @author Angel Asman
 * CSCI 330
 * 12-2-2015
 * Version 1
 * This program reads from johnson database and writes to asmana database the ticker and industry returns
 *
 */
public class stockDataMain extends StockSplit{
	static Connection conn = null;
	static Connection conn2 = null;
	static final String dropPerformanceTable = "drop table if exists Performance";
	static final String createPerformanceTable = "create table Performance (Industry char(30), Ticker char(6), StartDate char(10), EndDate char(10), TickerReturn char(12), IndustryReturn char(12))";
	static final String insertPerformance = "insert into Performance(Industry, Ticker, StartDate, EndDate, TickerReturn, IndustryReturn) values(?, ?, ?, ?, ?, ?)";
    static int tickerCount = 0;
	static int intervalSize = 0;

	public static void main(String[] args) throws Exception {
		// Get connection properties
		String ReaderparamsFile = "readerparams.txt";
		String WriterparamsFile = "writerparams.txt";
		if (args.length >= 1) {
			ReaderparamsFile = args[0];
			WriterparamsFile = args[1];
		}
		
		Properties connectprops = new Properties();
		Properties connectprops2 = new Properties();
		connectprops.load(new FileInputStream(ReaderparamsFile));
		connectprops2.load(new FileInputStream(WriterparamsFile));

		try {
			// Get connection
			Class.forName("com.mysql.jdbc.Driver");
			String dburl = connectprops.getProperty("dburl");
			String dburl2 = connectprops2.getProperty("dburl");
			String username = connectprops.getProperty("user");
			String username2 = connectprops2.getProperty("user");
			conn = DriverManager.getConnection(dburl, connectprops);
			conn2 = DriverManager.getConnection(dburl2, connectprops2);
			System.out.printf("Database connection %s %s established.%n",
					dburl, username);
			System.out.printf("Database connection %s %s established.%n",
					dburl2, username2);
			
			PreparedStatement Droptable = conn2.prepareStatement(dropPerformanceTable);
			Droptable.executeUpdate();
			Droptable.close();
		    PreparedStatement Ptable = conn2.prepareStatement(createPerformanceTable);
		    Ptable.executeUpdate();
		    Ptable.close();
			getIndustry();
            
			conn.close();
			conn2.close();

		} catch (SQLException ex) {
			System.out.printf(
					"SQLException: %s%nSQLState: %s%nVendorError: %s%n",
					ex.getMessage(), ex.getSQLState(), ex.getErrorCode());
		}
	}
	

	/**
	 * @throws SQLException
	 * gets Industry data from database
	 */
	static void getIndustry() throws SQLException {

		PreparedStatement pstmt = conn.prepareStatement("select Industry, count(distinct Ticker) as TickerCnt"
				+ " from Company natural join PriceVolume"
				+ " group by Industry"
				+ " order by Industry");
        
		ResultSet results = pstmt.executeQuery();
		while(results.next()) {
            tickerCount = results.getInt("TickerCnt");
			getDateRange(results.getString("Industry"));
			
		}

		pstmt.close();
	}
	
	/**
	 * @param industry the current industry
	 * @throws SQLException
	 * gets minMax and maxMin date range for each ticker in Industry
	 */
	static void getDateRange(String industry) throws SQLException {

		PreparedStatement pstmt = conn.prepareStatement("select Ticker, max(T.minDate) as minDate, min(T.maxDate) as maxDate"
				+ " from(select Ticker, min(TransDate) as minDate, max(TransDate) as maxDate,"
				+ " count(distinct TransDate) as TradingDays"
				+ " from Company natural join PriceVolume"
				+ " where Industry = ?"
				+ " group by Ticker"
				+ " having TradingDays >= 150"
				+ " order by Ticker) as T;");

		pstmt.setString(1, industry);
		ResultSet results = pstmt.executeQuery();

		//get date range for getTickerData
		if(results.next()) {
            getTickerData(results.getString("minDate"), results.getString("maxDate"),industry);
		}
		
		pstmt.close();
	}

	/**
	 * @param minDate the max of the min transdates
	 * @param maxDate the in of the max transdates
	 * @param industry the current industry
	 * @throws SQLException
	 * for each Industry object store a Hashmap of ticker keys with ticker data list as values
	 */
	static void getTickerData(String minDate, String maxDate, String industry) throws SQLException {
		//tickerCount = 7;
		PreparedStatement pstmt = conn.prepareStatement("select P.TransDate, P.openPrice, P.Ticker, P.closePrice"
				+ " from PriceVolume P natural join Company"
				+ " where Industry = ?"
				+ " and TransDate >= ? and TransDate <= ?"
				+ " order by TransDate, Ticker");

		pstmt.setString(1, industry);
		pstmt.setString(2, minDate);
		pstmt.setString(3, maxDate);
		ResultSet results = pstmt.executeQuery();
		Industry IndustryInfo = new Industry();
		IndustryInfo.setIndustryName(industry);
		
		while(results.next()) {
			Ticker tickerInfo = new Ticker();
			tickerInfo.setTickerName(results.getString("Ticker"));
			tickerInfo.setTransDate(results.getString("P.TransDate"));
			tickerInfo.setOpeningPrice(results.getDouble("P.openPrice"));
			tickerInfo.setClosingPrice(results.getDouble("P.closePrice"));
			
			if(!(tickerInfo.getTickerName().equals("PGN"))){			
			IndustryInfo.addToList(tickerInfo);
			IndustryInfo.addToMap(results.getString("Ticker"), tickerInfo);
			}
		}
		// loop through hashmap and do split adjustments and ticker returns on list values for ticker keys
		for (Entry<String, List<Ticker>> entry : IndustryInfo.getTickerMap().entrySet()) {
		    String key = entry.getKey();
		    List<Ticker> value = entry.getValue();
		    	splitCheck(value,key,IndustryInfo);
		    intervalSize = value.size()/60;
		}
		
		industryReturnCalc(IndustryInfo);		
		pstmt.close();
	}
		
	/**
	 * @param IndustryInfo
	 * @throws SQLException
	 * Calculates the industry returns for each ticker in interval
	 */
	static void industryReturnCalc(Industry IndustryInfo) throws SQLException{
		int count = 0;
		double industryReturn = 0.0;
		PreparedStatement pstmt = conn2.prepareStatement(insertPerformance);
		while (count <= intervalSize-1){
		for (Entry<String, List<TickerReturns>> entry : IndustryInfo.getReturnMap().entrySet()) {
		    String key = entry.getKey();
		    List<TickerReturns> value = entry.getValue();
		    double sum = 0.0;
		    		
				HashMap<String, List<TickerReturns>> ReturnMap = new HashMap<String, List<TickerReturns>>(IndustryInfo.getReturnMap());
				ReturnMap.remove(key);
				Iterator<String> iterator = ReturnMap.keySet().iterator();
				
				while(iterator.hasNext()){
				String nextKey = iterator.next();
				List<TickerReturns> listValue = IndustryInfo.getReturnMap().get(nextKey);
				sum += (listValue.get(count).getTickerReturns() + 1);
				}
				
				industryReturn = ((1/(double)(tickerCount-1))*sum) -1;
		        value.get(count).setIndustryReturns(industryReturn);
		        	      		        
		        pstmt.setString(1, IndustryInfo.getIndustryName());
		        pstmt.setString(2, value.get(count).getName());
		        pstmt.setString(3, value.get(count).getStartDate());
		        pstmt.setString(4, value.get(count).getEndDate());
		        pstmt.setString(5, String.format("%10.7f",value.get(count).getTickerReturns()));
		        pstmt.setString(6, String.format("%10.7f",value.get(count).getIndustryReturns()));
		        pstmt.executeUpdate();
		        		        
		 }		
		count++;
		
		}
		pstmt.close();
	}
		

	
}
