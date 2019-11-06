//
// Created by suun on 11/4/19.
//

#ifndef EFFECTIVE_CPP_STOCK_FACTORY_H
#define EFFECTIVE_CPP_STOCK_FACTORY_H

#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <mutex>

using Stock = std::string;

class StockFactory : public std::enable_shared_from_this<StockFactory> {
 private:
  mutable std::mutex mutex_;
  std::map<std::string, std::weak_ptr<Stock>> stocks_;

  static void destructStock(const std::weak_ptr<StockFactory> &, Stock *);
  void removeFromStocks(Stock *);
 public:
  StockFactory() = default;
  StockFactory(const StockFactory &) = delete;
  StockFactory &operator=(const StockFactory &) = delete;

  std::shared_ptr<Stock> get(const std::string &key);
};

void testLongLifeFactory();
void testShortLifeFactory();

#endif //EFFECTIVE_CPP_STOCK_FACTORY_H
