package csci330;

/**
 * @author Angel Asman
 * This class stores the tickerName and opening and closing prices
 *
 */
public class Ticker {

	private String tickerName;
	private String TransDate;
	private double openingPrice;
	private double closingPrice;

	/**
	 * @return the tickerName
	 */
	public String getTickerName() {
		return tickerName;
	}

	/**
	 * @param tickerName
	 *            the tickerName to set
	 */
	public void setTickerName(String tickerName) {
		this.tickerName = tickerName;
	}

	/**
	 * @return the minTransDate
	 */
	public String getTransDate() {
		return TransDate;
	}

	/**
	 * @param minTransDate
	 *            the minTransDate to set
	 */
	public void setTransDate(String TransDate) {
		this.TransDate = TransDate;
	}



	/**
	 * @return the openingPrice
	 */
	public double getOpeningPrice() {
		return openingPrice;
	}

	/**
	 * @param openingPrice the openingPrice to set
	 */
	public void setOpeningPrice(double openingPrice) {
		this.openingPrice = openingPrice;
	}

	/**
	 * @return the closingPrice
	 */
	public double getClosingPrice() {
		return closingPrice;
	}

	/**
	 * @param closingPrice the closingPrice to set
	 */
	public void setClosingPrice(double closingPrice) {
		this.closingPrice = closingPrice;
	}
}
