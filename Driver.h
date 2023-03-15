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
    std::map<int, Product *> bids;
    std::vector<User *> users;

  public:

    static Driver& getInstance() { // to get the instance of the Singleton class
      static Driver instance;

      return instance;
    }
    
    User * initializeUser(); // Initializes the human user
    void readUsers(); // reads from users.csv and initializes them
    void readHistoricalProducts(); // reads from products.csv and initializes them
    void run(); // simulates bidToBuy

    void addFinishedBid(int uid, Product * p) { finishedBids[uid] = p; } // adds a finished bid to the map
    void addActiveProducts(Product * p) { activeProducts.push_back(p); } // adds an active product to the list
    void addUser(User * u) { users.push_back(u); } // adds a user to the list

    void viewUsers(); // prints out current users
    void viewActiveProducts(Buyer * buya); // prints out current products

    std::map<int, Product *> getFinishedBids() const { return finishedBids; } // returns finished bids

    void menu(User * user); // menu for user

    Driver(Driver const&) = delete; // helps to implement  Singleton class
    void operator=(Driver const&) = delete; // helps to implement  Singleton class
};

#endif