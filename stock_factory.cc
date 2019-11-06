//
// Created by suun on 11/4/19.
//

#include "stock_factory.h"

std::shared_ptr<Stock> StockFactory::get(const std::string &key) {
  std::shared_ptr<Stock> pStock;
  std::lock_guard guard(mutex_);
  std::weak_ptr<Stock> &weakStock = stocks_[key];
  pStock = weakStock.lock();
  if (!pStock) {
    pStock.reset(
        new Stock(key), std::bind(
            &StockFactory::destructStock,
            std::weak_ptr<StockFactory>(shared_from_this()),
            std::placeholders::_1));
    weakStock = pStock;
  }
  return pStock;
}

void StockFactory::destructStock(
    const std::weak_ptr<StockFactory> &weakFactory,
    Stock *stock) {
  std::shared_ptr<StockFactory> factory(weakFactory.lock());
  if (factory) {
    factory->removeFromStocks(stock);
  }
  delete stock;
}

void StockFactory::removeFromStocks(Stock *stock) {
  if (stock) {
    std::lock_guard guard(mutex_);
    stocks_.erase(*stock);
  }
}
void testLongLifeFactory() {
  std::shared_ptr<StockFactory> factory(new StockFactory);
  {
    std::shared_ptr<Stock> stock = factory->get("IBM");
    auto stock2 = factory->get("IBM");
    assert(stock == stock2);
  }
}
void testShortLifeFactory() {
  std::shared_ptr<Stock> stock;
  {
    std::shared_ptr<StockFactory> factory(new StockFactory);
    stock = factory->get("IBM");
    auto stock2 = factory->get("IBM");
    assert(stock == stock2);
  }
}
