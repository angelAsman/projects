package csci330;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;

/**
 * @author Angel Asman
 * This program calculates the split and adjusts for them
 *
 */
public class StockSplit {
	
	/**
	 * @param iter the list iterator of ticker prices
	 * @param divisor the divisor from split ratio
	 * adjust the splits
	 */
	static public void adjustment(ListIterator<Ticker> iter,
			double divisor) {
		
		while (iter.hasNext()) {
			Ticker adjust = iter.next();
			adjust.setOpeningPrice(adjust.getOpeningPrice() / divisor);
			adjust.setClosingPrice(adjust.getClosingPrice() / divisor);
			iter.set(adjust);

		}
	}
	
	/**
	 * @param priceList the list of ticker prices
	 * @param key current ticker being analized
	 * @param IndustryInfo the current Industry object
	 * @throws SQLException
	 *  checks for splits in the list and calls adjustment function also does interval checks and ticker return
	 */
	static public void splitCheck(List<Ticker> priceList, String key, Industry IndustryInfo)
			throws SQLException {
		int count = 0;
	    double tickerReturn = 0.0;
	    double firstDayPrice = 0.0;
	    double lastDayPrice = 0.0;
	    String firstDate= "";
	    String lastDate= "";
	    List<TickerReturns> tickerList = new ArrayList<TickerReturns>();
		ListIterator<Ticker> listIterator = priceList.listIterator();

		while (listIterator.hasNext()) {
			Ticker currentDay = listIterator.next();
			TickerReturns returns = new TickerReturns();

			if (listIterator.hasNext()) {
				Ticker previousDay = listIterator.next();
				Double split = previousDay.getClosingPrice()
						/ currentDay.getOpeningPrice();

				if (Math.abs(split - 2.0) < 0.20) {

					ListIterator<Ticker> splitIter = priceList
							.listIterator(listIterator.previousIndex());

					adjustment(splitIter, 2);

				}
				if (Math.abs(split - 3.0) < 0.30) {

					ListIterator<Ticker> splitIter = priceList
							.listIterator(listIterator.previousIndex());

					adjustment(splitIter, 3);
				}
				if (Math.abs(split - 1.5) < 0.15) {

					ListIterator<Ticker> splitIter = priceList
							.listIterator(listIterator.previousIndex());

					adjustment(splitIter, 1.5);
				}
				
				if (count == 0){
			    	firstDayPrice = currentDay.getOpeningPrice();
			        firstDate = currentDay.getTransDate();		    	
				}
				
				count++;
				
				if(count == 60){
					
					returns.setEndDate(currentDay.getTransDate());
					returns.setStartDate(firstDate);
					lastDayPrice = currentDay.getClosingPrice();
					tickerReturn = (lastDayPrice/firstDayPrice) - 1;
					returns.setTickerReturns(tickerReturn);
					returns.setName(currentDay.getTickerName());
					tickerList.add(returns);
					count = 0;
				}
				
				if (listIterator.hasPrevious()) {
					currentDay = listIterator.previous();
					
				}

			}

		}

		IndustryInfo.addToReturns(key, tickerList);
        
	}

}


