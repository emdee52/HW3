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
    std::vector<Product *> activeProducts;
    std::vector<Product> bids;
    std::map<int, Product *> finishedBids;
    std::vector<User *> users;

  public:

    static Driver& getInstance() {
      static Driver instance;

      return instance;
    }
    
    void saveBidInfo(Product p);
    User * initializeUser();
    void run();

    void addFinishedBid(int uid, Product * p) { finishedBids[uid] = p; }
    void addActiveProducts(Product * p) { activeProducts.push_back(p); }
    void addBids(Product p);
    void addUser(User * u) { users.push_back(u); }

    void viewUsers();
    void viewActiveProducts();

    std::vector<Product> getActiveProducts();
    std::vector<Product> getBids();
    std::map<int, Product *> getFinishedBids() const { return finishedBids; }
    std::vector<User> getUsers();

    void menu(User * user);

    Driver(Driver const&) = delete;
    void operator=(Driver const&) = delete;
};

#endif