#pragma once
#include <cstdint>

enum class OrderSide {
    BUY,
    SELL
};

struct Order {
    uint64_t id;
    OrderSide side;
    double price;
    double quantity;
};

struct Trade {
    uint64_t maker_order_id; // ID ордера, который стоял в стакане
    uint64_t taker_order_id; // ID нового агрессивного ордера
    double price;            // Цена исполнения
    double quantity;         // Исполненный объем
};