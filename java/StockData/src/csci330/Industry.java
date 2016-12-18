package csci330;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * @author Angel Asman
 * This class stores the industry name and Ticker object list and 
 * two hashmaps which contain the intial ticker data and then the interval and ticker return data
 *
 */
public class Industry{
	
	private String industryName;
    private List<Ticker> tickerList = new ArrayList<Ticker>();
    
    private HashMap<String, List<Ticker>> tickerMap = new HashMap<String, List<Ticker>>();
    private HashMap<String, List<TickerReturns>> ReturnMap = new HashMap<String, List<TickerReturns>>();
    private List<String> intervals = new ArrayList<String>();
    
    public void addToList(Ticker tickerInfo){
    	tickerList.add(tickerInfo);
    }

	/**
	 * @return the industryName
	 */
	public String getIndustryName() {
		return industryName;
	}

	/**
	 * @param industryName
	 *            the industryName to set
	 */
	public void setIndustryName(String industryName) {
		this.industryName = industryName;
	}

	/**
	 * @return the tickerList
	 */
	public List<Ticker> getTickerList() {
		return tickerList;
	}

	/**
	 * @param tickerList the tickerList to set
	 */
	public void setTickerList(List<Ticker> tickerList) {
		this.tickerList = tickerList;
	}
	
	
	/**
	 * @return tickerMap
	 */
	public HashMap<String, List<Ticker>> getTickerMap(){
		return tickerMap;
	}
	
	/**
	 * @param ticker the current ticker in industry
	 * @param tokens the actual ticker object
	 */
	public void addToMap(String ticker, Ticker tokens) {
		if (tickerMap.containsKey(ticker)) {
			List<Ticker> oldList = new ArrayList<Ticker>();
			oldList = tickerMap.get(ticker);
			oldList.add(tokens);
			tickerMap.put(ticker, oldList);
		} else {
			List<Ticker> newList = new ArrayList<Ticker>();
			newList.add(tokens);
			tickerMap.put(ticker, newList);
		}

	}

	
	public void addToReturns(String tick, List<TickerReturns> tickList){
		ReturnMap.put(tick, tickList);
	}
	/**
	 * @return the returnMap
	 */
	public HashMap<String, List<TickerReturns>> getReturnMap() {
		return ReturnMap;
	}

	/**
	 * @param returnMap the returnMap to set
	 */
	public void setReturnMap(HashMap<String, List<TickerReturns>> returnMap) {
		ReturnMap = returnMap;
	}

}
