#pragma once
#include "types.h"
#include <map>
#include <queue>

class OrderBook {
private:
    // Bids: сортировка по убыванию цены (std::greater)
    std::map<double, std::queue<Order>, std::greater<double>> bids;
    
    // Asks: сортировка по возрастанию цены (по умолчанию)
    std::map<double, std::queue<Order>> asks;

public:
    // Добавление лимитного ордера в стакан
    void add_limit_order(const Order& order) {
        if (order.side == OrderSide::BUY) {
            bids[order.price].push(order);
        } else {
            asks[order.price].push(order);
        }
    }

    // Получение лучших цен для аналитики
    double get_best_bid() const {
        return bids.empty() ? 0.0 : bids.begin()->first;
    }

    double get_best_ask() const {
        return asks.empty() ? 0.0 : asks.begin()->first;
    }
};