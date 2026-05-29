#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "MarketDataEvent.hpp"

using json = nlohmann::json;

// Consumer function
void processMarketDataEvent(const MarketDataEvent& event) {
    std::cout << "Processing event: ";
    event.print();
}

int main(int argc, char* argv[]) {
    // Check command line argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_json_file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<MarketDataEvent> events;
    std::string line;
    int line_count = 0;
    std::string first_timestamp = "";
    std::string last_timestamp = "";

    // Read file line by line (NDJSON)
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        try {
            // Parse JSON
            json j = json::parse(line);
            
            // Extract required fields
            std::string timestamp = j.value("ts_recv", "");
            std::string order_id = j.value("order_id", "");
            std::string side = j.value("side", "");
            std::string price_str = j.value("price", "");
            double price = 0.0;
            if (!price_str.empty()) {
                try {
                    price = std::stod(price_str);
                } catch (const std::exception&) {
                    // Handle invalid price
                }
            }
            int size = j.value("size", 0);
            std::string action = j.value("action", "");
            
            // Create MarketDataEvent
            MarketDataEvent event(timestamp, order_id, side, price, size, action);
            
            // Store event
            events.push_back(event);
            
            // Set first timestamp
            if (first_timestamp.empty()) {
                first_timestamp = timestamp;
            }
            
            // Update last timestamp
            last_timestamp = timestamp;
            
            // Process every event
            processMarketDataEvent(event);
            
            line_count++;
            
        } catch (const std::exception& e) {
            std::cerr << "Error parsing JSON on line " << line_count + 1 << ": " << e.what() << std::endl;
            continue;
        }
    }
    
    file.close();

    // Summary
    std::cout << "\n--- Summary ---" << std::endl;
    std::cout << "Total messages processed: " << line_count << std::endl;
    std::cout << "First timestamp: " << first_timestamp << std::endl;
    std::cout << "Last timestamp: " << last_timestamp << std::endl;

    // Print first 10 events
    std::cout << "\nFirst 10 events:" << std::endl;
    int first_n = std::min(10, static_cast<int>(events.size()));
    for (int i = 0; i < first_n; i++) {
        events[i].print();
    }

    // Print last 10 events
    std::cout << "\nLast 10 events:" << std::endl;
    int last_n = std::min(10, static_cast<int>(events.size()));
    int start_idx = events.size() - last_n;
    for (int i = start_idx; i < events.size(); i++) {
        events[i].print();
    }

    return 0;
}