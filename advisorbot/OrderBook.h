#pragma once
#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <vector>
#include <string>

class OrderBook
{
public:
	/*construct, reading a csv data file*/
	OrderBook(std::string filename);

	/*Return vector of all know products in the dataset*/
	std::vector<std::string>getKnownProducts();

	/*Return vector of Orders according to the sent filters*/
	std::vector<OrderBookEntry>getOrders(OrderBookType orderType, std::string product, std::string timestamp);

	/*Return the earliest time in the orderbook*/
	std::string getEarliestTime();

	/*Return the next time after the sent time in the orderbook*/
	/*If there is no next timestamp,wraps around to the start*/
	std::string getNextTime(std::string timestamp);

	void insertOrder(OrderBookEntry& order);

	std::vector<OrderBookEntry>matchAskToBids(std::string product, std::string timestamp);

	static double getHighPrice(std::vector <OrderBookEntry>& orders);
	static double getLowPrice(std::vector <OrderBookEntry>& orders);
	static double getTotalPrice(std::vector <OrderBookEntry>& orders);

private:
	std::vector<OrderBookEntry> orders;
};

