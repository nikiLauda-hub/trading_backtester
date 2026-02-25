# High-Performance Algorithmic Trading Backtester

![C++](https://img.shields.io/badge/Core-C++17-blue.svg)
![Python](https://img.shields.io/badge/Interface-Python3-yellow.svg)
![Build](https://img.shields.io/badge/Build-CMake-green.svg)

A hybrid trading backtesting engine designed for high-frequency trading (HFT) simulations. It combines the raw performance of **C++** for the matching engine and order book management with the flexibility of **Python** for data analysis and strategy implementation.

## 🚀 Key Features

* **Hybrid Architecture:** Core logic written in C++17, exposed to Python via `pybind11`.
* **Limit Order Book (LOB):** Full implementation of a standard LOB with price-time priority (FIFO).
* **Matching Engine:** Real-time order matching logic that simulates market execution mechanics.
* **Performance:** Optimized for low-latency simulations.
* **Detailed Reporting:** Returns execution details (Trades) for every processed order.

## 🛠 Project Structure

```text
├── core/             # C++ source code (Performance critical)
│   ├── main.cpp      # Python bindings entry point
│   ├── order_book.h  # LOB and Matching Engine logic
│   └── types.h       # Data structures (Order, Trade, Side)
├── scripts/          # Python strategies and data loaders
├── extern/           # Third-party libraries (pybind11)
├── CMakeLists.txt    # Build configuration
└── README.md         # Project documentation
```

## ⚙️ Installation & Build

### Prerequisites
* C++ Compiler (Clang/GCC/MSVC) supporting C++17
* CMake (3.20+)
* Python (3.8+)

### 1. Clone the repository
```bash
git clone --recursive https://github.com/nikiLauda-hub/trading_backtester.git
cd trading_backtester
```

### 2. Build with CMake
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

Note: The build process automatically copies the compiled extension (.so or .pyd) to the scripts/ directory.


## ⚡ Usage Example

You can import the C++ core directly into your Python scripts.
```python
import sys
import os

# Ensure the compiled module is in the path
sys.path.append(os.path.join(os.path.dirname(__file__), '../scripts'))

from backtest_core import OrderBook, Order, OrderSide

def run_simulation():
    # Initialize the C++ Order Book
    book = OrderBook()

    # Create a Limit Order (ID, Side, Price, Quantity)
    # Buy 1.5 BTC at $99.5
    buy_order = Order(1, OrderSide.BUY, 99.5, 1.5)
    
    # Sell 0.5 BTC at $99.5 (This will match immediately)
    sell_order = Order(2, OrderSide.SELL, 99.5, 0.5)

    # Process orders through the engine
    print("Processing Buy Order...")
    trades_buy = book.process_order(buy_order)
    
    print(f"Processing Sell Order (Aggressive)...")
    trades_sell = book.process_order(sell_order)

    # Output results
    for trade in trades_sell:
        print(f"Trade Executed: {trade.quantity} units @ ${trade.price}")
        print(f"Maker Order ID: {trade.maker_order_id} | Taker Order ID: {trade.taker_order_id}")

    # Check current market state
    print(f"Best Bid: {book.get_best_bid()}")
    print(f"Best Ask: {book.get_best_ask()}")

if __name__ == "__main__":
    run_simulation()
```

## 🗺 Roadmap
- [x] Basic Limit Order Book (LOB)
- [x] Matching Engine (Core Logic)
- [x] Python Bindings via pybind11
- [ ] Historical Data Parser (CSV/HDF5)
- [ ] Strategy Base Class in Python
- [ ] PnL and Max Drawdown calculation module

## 📄 License
This project is open-source and available under the MIT License.