#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <iostream>
#include "User.h"
#include <map>

class Driver{
  private:
    Driver(){
      activeProducts = {};
      users = {};
    };
    std::vector<Product *> activeProducts;
    std::map<int, Product *> finishedBids;
    std::vector<User *> users;

  public:

    static Driver& getInstance() {
      static Driver instance;

      return instance;
    }
    
    void saveBidInfo(Product p);
    User * initializeUser();
    void readUsers();
    void readHistoricalProducts();
    void run();

    void addFinishedBid(int uid, Product * p) { finishedBids[uid] = p; }
    void addActiveProducts(Product * p) { activeProducts.push_back(p); }
    void addUser(User * u) { users.push_back(u); }

    void viewUsers();
    void viewActiveProducts(Buyer * buya);

    std::vector<Product> getActiveProducts();
    std::map<int, Product *> getFinishedBids() const { return finishedBids; }
    std::vector<User> getUsers();

    void menu(User * user);

    Driver(Driver const&) = delete;
    void operator=(Driver const&) = delete;
};

#endif