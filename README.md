# Event-Driven Backtester

A C++ event-driven backtesting framework for financial market data analysis. The system reads market data from JSON files, processes it as events, and provides a foundation for building trading strategies and limit order book simulations.

## Features

- **Event-Driven Architecture**: Processes market data as discrete events
- **NDJSON Support**: Reads market data from Newline-Delimited JSON files
- **Market Data Processing**: Parses and normalizes market data messages
- **Flexible Design**: Extensible event system for building trading strategies
- **CMake Build System**: Modern C++ build configuration with automatic dependency management

## Project Structure

```
backtest/
├── data/                    # Market data files (NDJSON format)
├── scr/                     # Source code
│   ├── MarketDataEvent.hpp  # Market data event class
│   └── data_processor.cpp   # Main data processing program
├── test/                    # Unit tests (future)
├── build/                   # Build output directory
├── CMakeLists.txt          # CMake configuration
└── README.md               # Project documentation
```

## Build Instructions

### Prerequisites

- C++17 compatible compiler (MSVC, GCC, or Clang)
- CMake 3.16 or higher
- Git (for dependency management)

### Building the Project

1. Clone the repository and navigate to the project directory
2. Create a build directory and configure the project:

```bash
cd backtest
mkdir build
cd build
cmake ..
```

3. Build the project:

```bash
# On Linux/Mac
make

# On Windows (using Visual Studio)
cmake --build .
```

The build system uses FetchContent to automatically download the nlohmann/json library, so no additional dependencies need to be installed manually.

## Running the Data Processor

The data processor reads market data from NDJSON files and outputs event information:

```bash
# From the build directory

# On Linux/Mac
./data_processor ../data/XEUR-20260409-HJTR7RCAKT/xeur-eobi-20260309.mbo.json

# On Windows
Debug\\data_processor.exe ..\\data\\XEUR-20260409-HJTR7RCAKT\\xeur-eobi-20260309.mbo.json
```

## Example Output

```
Processing event: Timestamp: 2026-03-17T08:30:46.825615195Z, OrderID: 0, Side: N, Price: 0.000000, Size: 0, Action: R
Processing event: Timestamp: 2026-03-17T08:30:46.825615195Z, OrderID: 10997108283680095064, Side: B, Price: 0.020900, Size: 20, Action: A

--- Summary ---
Total messages processed: 15000
First timestamp: 2026-03-17T08:30:46.825615195Z
Last timestamp: 2026-03-17T15:29:59.999999999Z

First 10 events:
Timestamp: 2026-03-17T08:30:46.825615195Z, OrderID: 0, Side: N, Price: 0.000000, Size: 0, Action: R
...
Last 10 events:
Timestamp: 2026-03-17T15:29:59.999999999Z, OrderID: 987654321, Side: B, Price: 1.123450, Size: 50, Action: A
```

## Data Format

The processor handles NDJSON (Newline-Delimited JSON) files where each line is a separate JSON object representing a market data event. The expected fields are:

- `ts_recv`: Receive timestamp
- `order_id`: Unique order identifier
- `side`: Order side (B=bid, A=ask, N=none)
- `price`: Order price (can be null)
- `size`: Order quantity
- `action`: Action type (A=add, R=remove, M=modify)