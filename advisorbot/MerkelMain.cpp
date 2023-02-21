#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <vector>
#include <iostream>

MerkelMain::MerkelMain() {

}

void MerkelMain::init() {
    std::string input;
    currentTime = orderBook.getEarliestTime();

    while (true) {
        input = getUserOption();
        processUserOption(input);
    }
}

std::string MerkelMain::getUserOption()
{
    std::string userOption;
    std::cout << "=======================" << std::endl;
    std::cout << "Welcome to Advisorbot "<<std::endl;
    std::cout << "=======================" << std::endl; 
    std::cout << "Please enter a command, or help for a list of commands :";
    std::getline(std::cin, userOption);
    return userOption;
}

//list all available command
void MerkelMain::printHelp()
{
    std::cout << "=====================================";
    std::cout << "\n The available commands are: " << std::endl;
    std::cout << "=====================================";
    std::cout << "\n >> help \n >> help <cmd> \n >> prod \n >> min \n >> max \n >> avg \n >> predict\n >> time \n >> step \n >> printstats" << std::endl;
    std::cout << "=====================================" << std::endl;
}

//output help for the specific command
void MerkelMain::processHelpCommand(std::string userOption) {
    std::vector <std::string> tokens = CSVReader::tokenise(userOption, ' ');
    try
    {
        if (tokens[1] == "min")
        {
            std::cout << "=================" << std::endl;
            std::cout << "  min command" << std::endl;
            std::cout << "=================" << std::endl;
            std::cout << "Command: >> min product bid/ask" << std::endl;
            std::cout << "Example: >> min ETH/BTC ask " << std::endl;
            std::cout << "Output : -> The min ask for ETH/BTC is 1.0" << std::endl;
        }

        else if (tokens[1] == "max")
        {
            std::cout << "=================" << std::endl;
            std::cout << "  max command" << std::endl;
            std::cout << "=================" << std::endl;
            std::cout << "Command: >> max product bid/ask" << std::endl;
            std::cout << "Example: >> max ETH/BTC ask " << std::endl;
            std::cout << "Output : -> The max ask for ETH/BTC is 1.0" << std::endl;
        }

        else if (tokens[1] == "avg")
        {
            std::cout << "=================" << std::endl;
            std::cout << "  avg command" << std::endl;
            std::cout << "=================" << std::endl;
            std::cout << "Command: >> avg product bid/ask timesteps" << std::endl;
            std::cout << "Example: >> avg ETH/BTC ask 10 " << std::endl;
            std::cout << "Output : -> The average ETH/BTC ask price over the last 10 timesteps was 1.0" << std::endl;
        }

        else if (tokens[1] == "predict")
        {
            std::cout << "=================" << std::endl;
            std::cout << " predict command" << std::endl;
            std::cout << "=================" << std::endl;
            std::cout << "Command: >> predict max/min product bid/ask" << std::endl;
            std::cout << "Example: >> predict max ETH/BTC bid " << std::endl;
            std::cout << "Output : -> The average ETH/BTC ask price over the last 10 timesteps was 1.0" << std::endl;
        }

        else
        {
            std::cout << "Invalid command. Please enter help to choose available commands." << std::endl;
        }
    }catch (const  std::exception& e){   
        std::cout << "MerkelMain::processHelpCommand Error.Please check again." << std::endl;
    }
}

//list available products
void MerkelMain::printProducts()
{
    int i = 1;
    std::cout << "============= " << std::endl;
    std::cout << "  Products " << std::endl;
    std::cout << "============= " << std::endl;
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::cout << i<<". " << p << std::endl;
        i++;        
    }
}

//find minimum bid or ask for product in current time step
void MerkelMain::printMin(std::string userOption)
{
    // Tokens[0]:command, Tokens[1]:Product, Tokens[2]:Bid/Ask
    std::vector <std::string> tokens = CSVReader::tokenise(userOption, ' ');

    try
    {
        if (tokens[2] == "ask")
        {
            std::vector <OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, tokens[1], currentTime);
            std::cout << "The min " << tokens[2] << " for " << tokens[1] << " is " << orderBook.getLowPrice(entries) << std::endl;
        }

        else if (tokens[2] == "bid")
        {
            std::vector <OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, tokens[1], currentTime);
            std::cout << "The min " << tokens[2] << " for " << tokens[1] << " is " << orderBook.getLowPrice(entries) << std::endl;
        }

        else
        {
            std::cout << "Invalid command. Please enter help to choose available commands." << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "MerkelMain::printMin Error." << std::endl;
    }
}

//find maximum bid or ask for product in current time step
void MerkelMain::printMax(std::string userOption) {
    // Tokens[0]:command, Tokens[1]:Product, Tokens[2]:Bid/Ask
    std::vector <std::string> tokens = CSVReader::tokenise(userOption, ' ');

    try
    {
        if (tokens[2] == "ask")
        {
            std::vector <OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, tokens[1], currentTime);
            std::cout << "The max " << tokens[2] << " for " << tokens[1] << " is " << orderBook.getHighPrice(entries) << std::endl;
        }

        else if (tokens[2] == "bid")
        {
            std::vector <OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, tokens[1], currentTime);
            std::cout << "The max " << tokens[2] << " for " << tokens[1] << " is " << orderBook.getHighPrice(entries) << std::endl;
        }

        else
        {
            std::cout << "Invalid command. Please enter help to choose available commands." << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "MerkelMain::printMax Error." << std::endl;
    }
}

//compute average or bid for the sent product over the sent number of time steps
void MerkelMain::printAverage(std::string userOption) {
    // Tokens[0]:command, Tokens[1]:Product, Tokens[2]:Bid/Ask,Tokens[3]:Timesteps
    std::vector <std::string> tokens = CSVReader::tokenise(userOption, ' ');
    double totalPrice = 0.0;
    int totalEntries = 0;
    
    int timesteps = stoi(tokens[3]);

    try
    {
        for (int i = 0; i < timesteps; i++)
        {
            if (tokens[2] == "ask")
            {
                std::vector <OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, tokens[1], currentTime);
                totalPrice = orderBook.getTotalPrice(entries) + totalPrice;
                totalEntries = entries.size() + totalEntries;
                std::cout << "Ask totalPrice: " << totalPrice << std::endl;
                std::cout << "Ask totalEntries: " << totalEntries << std::endl;
            }

            else if (tokens[2] == "bid")
            {
                std::vector <OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, tokens[1], currentTime);
                totalPrice = orderBook.getTotalPrice(entries) + totalPrice;
                totalEntries = entries.size() + totalEntries;
                std::cout << "Bid totalPrice: " << totalPrice << std::endl;
                std::cout << "Bid totalEntries: " << totalEntries << std::endl;
            }

            else
            {
                std::cout << "Something error.Please try again." << std::endl;
            }     
        }
        std::cout << "The Average " << tokens[1] <<" "<< tokens[2] << " price over the last " << tokens[3] << " was " << totalPrice / totalEntries << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "MerkelMain::printAverage Error" << std::endl;
    }
}

//predict max or min ask or bid for the sent product for the next time
void MerkelMain::printPredict() {
}

//shows how many successful matching transaction
void MerkelMain::printMatchStats() {
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "================================" << std::endl;
        std::cout << "Matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAskToBids(p, currentTime);
        std::cout << "Total sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " Amount " << sale.amount << std::endl;
        }

        std::cout << "================================" << std::endl;
    }
}

//state current time in dataset,i.e which timeframe are we looking at
void MerkelMain::printCurrentTime() {
    std::cout << "Current time is : " << currentTime << std::endl;
}

//move to next time step
void MerkelMain::gotoNextStep()
{
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << "Now at " << currentTime << std::endl;
}

void MerkelMain::processUserOption(std::string userOption) {
    std::vector <std::string> tokens = CSVReader::tokenise(userOption, ' ');
    try {
    
        if (tokens.size() == 1)   
        {    
            if (tokens[0] == "help")        
            {         
                printHelp();      
            }
      
            else if (tokens[0] == "prod")       
            {        
                printProducts();     
            }
    
            else if (tokens[0] == "time")    
            {              
                printCurrentTime();
            }
    
            else if (tokens[0] == "step") 
            {       
                gotoNextStep();    
            }
            else if (tokens[0] == "printstats") 
            {
                printMatchStats();
            }

            else
            {
                std::cout << "Invalid command. Please enter help to choose available commands." << std::endl;
            }
        }
 
        else if (tokens.size() == 2)  
        {      
            if (tokens[0] == "help")     
            {       
                processHelpCommand(userOption);    
            }
       
            else      
            {        
                std::cout << "Invalid command. Please enter help to choose available commands." << std::endl;
            } 
        }   
        
        else if (tokens.size() == 3)
        {
            if (tokens[0] == "min")
            {
                printMin(userOption);
            }

            else if (tokens[0] == "max")
            {
                printMax(userOption);
            }

            else
            {
                std::cout << "Invalid command. Please enter help to choose available commands." << std::endl;
            }
        }

        else if (tokens.size() == 4)
        {
            if (tokens[0] == "avg")
            {
                printAverage(userOption);
            }

            else if (tokens[0] == "predict")
            {
                printPredict();
            }

            else
            {
                std::cout << "Invalid command. Please enter help to choose available commands." << std::endl;
            }
        }

        else
        {
            std::cout << "Invalid command. Please enter help to choose available commands." << std::endl;
        }
    }catch (const  std::exception& e) {   
        std::cout << "MerkelMain::processUserOption Error." << std::endl;
    }
}

