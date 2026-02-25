from backtest_core import Order, OrderSide, OrderBook

# Инициализация стакана
book = OrderBook()

# Создание заявок: id, сторона, цена, объем
order1 = Order(1, OrderSide.BUY, 99.5, 1.5)
order2 = Order(2, OrderSide.BUY, 100.0, 2.0)   # Эта цена лучше для продавца
order3 = Order(3, OrderSide.SELL, 101.5, 0.5)
order4 = Order(4, OrderSide.SELL, 102.0, 1.0)

# Отправка заявок в C++ ядро
book.add_limit_order(order1)
book.add_limit_order(order2)
book.add_limit_order(order3)
book.add_limit_order(order4)

print(f"Лучшая цена покупки (Bid): {book.get_best_bid()}")
print(f"Лучшая цена продажи (Ask): {book.get_best_ask()}")