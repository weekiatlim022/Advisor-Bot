#pragma once
#include<vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class MerkelMain
{
public:
    MerkelMain();
    /** Call this to start the sim */
    void init();

private:
    
    std::string getUserOption();    
    void printHelp();
    void processHelpCommand(std::string userOption);
    void printProducts();
    void printMin(std::string userOption);
    void printMax(std::string userOption);
    void printAverage(std::string userOption);
    void printPredict();
    void printMatchStats();
    void printCurrentTime();
    void gotoNextStep();
    void processUserOption(std::string userOption);

    std::string currentTime;

    OrderBook orderBook{"20200601.csv"};
    
};

