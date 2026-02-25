#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "types.h"
#include "order_book.h"

namespace py = pybind11;

PYBIND11_MODULE(backtest_core, m) {
    // Связываем enum OrderSide
    py::enum_<OrderSide>(m, "OrderSide")
        .value("BUY", OrderSide::BUY)
        .value("SELL", OrderSide::SELL)
        .export_values();

    // Связываем структуру Order
    py::class_<Order>(m, "Order")
        .def(py::init<uint64_t, OrderSide, double, double>()) // Конструктор для Python
        .def_readwrite("id", &Order::id)
        .def_readwrite("side", &Order::side)
        .def_readwrite("price", &Order::price)
        .def_readwrite("quantity", &Order::quantity);

    // Связываем структуру Trade
    py::class_<Trade>(m, "Trade")
        .def(py::init<uint64_t, uint64_t, double, double>())
        .def_readwrite("maker_order_id", &Trade::maker_order_id)
        .def_readwrite("taker_order_id", &Trade::taker_order_id)
        .def_readwrite("price", &Trade::price)
        .def_readwrite("quantity", &Trade::quantity);

    // Связываем класс OrderBook
    py::class_<OrderBook>(m, "OrderBook")
        .def(py::init<>())
        .def("process_order", &OrderBook::process_order)
        .def("get_best_bid", &OrderBook::get_best_bid)
        .def("get_best_ask", &OrderBook::get_best_ask);
}