#ifndef _USER_H_
#define _USER_H_
#include <iostream>
#include <vector>
#include "Product.h"
#include <string>
#include <iostream>

class User;

enum class UserType{SELLER, BUYER, USER};

// struct Message;
struct Message{
  std::string data;
  User * from;
  User * to;
};

class User{
  protected:
    double balance_;
    int id_;
    std::string name_;
    std::string address_;
    std::string phone_;
    std::vector<Message> messages_;
    UserType type;
    static int count;

  public:
    User(){}
    User(double balance, std::string name, std::string addy, std::string phone) : id_(++count), balance_(balance), name_(name), address_(addy), phone_(phone){}
    
    // Setters
    void setBalance(double bal) { balance_ = bal; }
    void setId(int id) { id_ = id; }
    void setName(std::string name) { name_ = name; }
    void setAddress(std::string addy) { address_ = addy; }
    void setPhone(std::string phone) { phone_ = phone; }
    void addMessage(Message message) { messages_.push_back(message); }

    void updateInfo(); // update user info interface

    // Getters
    double getBalance() const { return balance_; }
    int getId() const { return id_; }
    std::string getName() const { return name_; }
    std::string getAddress() const { return address_; }
    std::string getPhone() const { return phone_; }
    UserType getType() const { return type; }

    bool printMessages(); // prints all current messages
    void viewMessages(); // view messages/respond to interface
    void viewBalance(); // view balance interface
    void respond(int index); // respond to messages

    virtual void overview(){}; // empty for the parent class
    static User* userFactory(UserType type, double balance, std::string name, std::string addy, std::string phone); // generates a user instance based on params
};

class Seller: public User{
  private:
    std::vector<Product *> products;
    std::vector<Product *> soldProducts;
  public:
    Seller(){ type = UserType::SELLER; }
    Seller(double balance, std::string name, std::string addy, std::string phone) : User(balance, name, addy, phone){
      type = UserType::SELLER;
    }

    Product * addProductForSale(); // interface to list a product for sale
    void productSold(Product * p); // sells a product, removes it from list
    void viewProducts(); // prints out the list of products
    void viewSoldProducts(); // prints out the list of sold products
    std::vector<Product *> getProducts() { return products; } // returns the products vector
    void overview(); // Seller overview including user info, products, sold products
    std::map<bool, Product *> assignBidStatus(); // open/close bids

};

class Buyer: public User{
  private:
    std::vector<Product *> purchases;
    std::map<int, double> bids;
  public:
    Buyer(){ type = UserType::BUYER; }
    Buyer(double balance, std::string name, std::string addy, std::string phone) : User(balance, name, addy, phone){
      type = UserType::BUYER;
    }
    void addBidToProduct(int pid, double bid); // adds buyer's bid to a product
    void viewPurchases(); // views won bids
    void sendMessage(User &to); // send a message to buyer whose product you earned
    void overview(); // get an overview of your bids
};

#endif