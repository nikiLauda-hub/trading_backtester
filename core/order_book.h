#pragma once
#include "types.h"
#include <map>
#include <queue>
#include <vector>
#include <algorithm> // для std::min

class OrderBook {
private:
    std::map<double, std::queue<Order>, std::greater<double>> bids;
    std::map<double, std::queue<Order>> asks;

public:
    // Метод принимает копию ордера, так как его объем будет меняться в процессе сведения
    std::vector<Trade> process_order(Order order) {
        std::vector<Trade> trades;

        if (order.side == OrderSide::BUY) {
            // Ищем подходящих продавцов: пока объем больше 0 и есть ордера на продажу
            while (order.quantity > 0 && !asks.empty()) {
                auto best_ask = asks.begin();
                if (best_ask->first > order.price) {
                    break; // Лучшая цена продажи выше, чем готов заплатить покупатель
                }

                auto& queue = best_ask->second;
                auto& maker_order = queue.front();

                // Объем сделки — это минимум из того, что нужно купить, и того, что есть в стакане
                double trade_quantity = std::min(order.quantity, maker_order.quantity);
                trades.push_back({maker_order.id, order.id, best_ask->first, trade_quantity});

                order.quantity -= trade_quantity;
                maker_order.quantity -= trade_quantity;

                // Удаляем исполненный ордер из очереди
                if (maker_order.quantity == 0) {
                    queue.pop();
                }
                // Если по этой цене больше нет ордеров, удаляем уровень цены
                if (queue.empty()) {
                    asks.erase(best_ask);
                }
            }
            // Если после сведения остался неисполненный объем, добавляем его в bids
            if (order.quantity > 0) {
                bids[order.price].push(order);
            }
        } else { // SELL
            // Ищем подходящих покупателей
            while (order.quantity > 0 && !bids.empty()) {
                auto best_bid = bids.begin();
                if (best_bid->first < order.price) {
                    break; // Лучшая цена покупки ниже, чем готов продать продавец
                }

                auto& queue = best_bid->second;
                auto& maker_order = queue.front();

                double trade_quantity = std::min(order.quantity, maker_order.quantity);
                trades.push_back({maker_order.id, order.id, best_bid->first, trade_quantity});

                order.quantity -= trade_quantity;
                maker_order.quantity -= trade_quantity;

                if (maker_order.quantity == 0) {
                    queue.pop();
                }
                if (queue.empty()) {
                    bids.erase(best_bid);
                }
            }
            if (order.quantity > 0) {
                asks[order.price].push(order);
            }
        }

        return trades;
    }

    double get_best_bid() const {
        return bids.empty() ? 0.0 : bids.begin()->first;
    }

    double get_best_ask() const {
        return asks.empty() ? 0.0 : asks.begin()->first;
    }
};