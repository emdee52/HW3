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
    std::vector<Product> activeProducts;
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

    void addFinishedBid(int id, Product * p) { finishedBids[id] = p; }
    void addActiveProducts(Product p);
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