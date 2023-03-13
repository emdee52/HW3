#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <iostream>
#include "User.h"
#include <map>

class Driver{
  private:
    Driver(){
      activeProducts = {};
      bids = {};
      users = {};
    };
    std::map<int, Product *> activeProducts;
    std::vector<Product> bids;
    std::map<int, Product *> finishedBids;
    std::vector<User> users;

  public:

    static Driver& getInstance() {
      static Driver instance;

      return instance;
    }
    
    void saveBidInfo(Product p);
    void run(User u);

    void addFinishedBid(int uid, Product * p) { finishedBids[uid] = p; }
    void addActiveProducts(int uid, Product * p) { activeProducts[uid] = p; }
    void addBids(Product p);
    void addUsers(User u);

    std::vector<Product> getActiveProducts();
    std::vector<Product> getBids();
    std::map<int, Product *> getFinishedBids() const { return finishedBids; }
    std::vector<User> getUsers();

    Driver(Driver const&) = delete;
    void operator=(Driver const&) = delete;
};

#endif