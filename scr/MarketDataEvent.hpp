#pragma once
#include <string>
#include <iostream>

class MarketDataEvent {
private:
    std::string timestamp;
    std::string order_id;
    std::string side;
    double price;
    int size;
    std::string action;

public:
    // Constructor
    MarketDataEvent(const std::string& ts, const std::string& oid, const std::string& s, double p, int sz, const std::string& act)
        : timestamp(ts), order_id(oid), side(s), price(p), size(sz), action(act) {}

    // Print function
    void print() const {
        std::cout << "Timestamp: " << timestamp
                  << ", OrderID: " << order_id
                  << ", Side: " << side
                  << ", Price: " << price
                  << ", Size: " << size
                  << ", Action: " << action << std::endl;
    }
};