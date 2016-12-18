package csci330;

/**
 * @author Angel Asman
 * This class stores the interval dates and ticker returns and industry returns
 * and ticker name
 *
 */
public class TickerReturns {
	private String startDate;
	private String endDate;
	private String name;
	private double tickerReturns;
	private double industryReturns;
	/**
	 * @return the startDate
	 */
	public String getStartDate() {
		return startDate;
	}
	/**
	 * @param startDate the startDate to set
	 */
	public void setStartDate(String startDate) {
		this.startDate = startDate;
	}
	/**
	 * @return the endDate
	 */
	public String getEndDate() {
		return endDate;
	}
	/**
	 * @param endDate the endDate to set
	 */
	public void setEndDate(String endDate) {
		this.endDate = endDate;
	}
	/**
	 * @return the tickerReturns
	 */
	public double getTickerReturns() {
		return tickerReturns;
	}
	/**
	 * @param tickerReturns the tickerReturns to set
	 */
	public void setTickerReturns(double tickerReturns) {
		this.tickerReturns = tickerReturns;
	}
	/**
	 * @return the industryReturns
	 */
	public double getIndustryReturns() {
		return industryReturns;
	}
	/**
	 * @param industryReturns the industryReturns to set
	 */
	public void setIndustryReturns(double industryReturns) {
		this.industryReturns = industryReturns;
	}
	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}
	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}
}
