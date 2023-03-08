#ifndef _USER_H_
#define _USER_H_
#include <iostream>
#include <vector>
#include "Product.h"
class User{
  private:
    double balance_;
    int id_;
    std::string name_;
    std::string address_;
    std::string phone_;
    std::vector<std::string> messages_;
  public:
    void setBalance(double bal);
    void setId(int id);
    void setName(std::string name);
    void setAddress(std::string addy);
    void setPhone(std::string phone);
    void addMessage(std::string message);

    double getBalance();
    int getId();
    std::string getName();
    std::string getAddress();
    std::string getPhone();
    std::vector<std::string> viewMessages();
    void respond(User to);
    virtual bool overview(){};
};

class Seller: public User{
  private:
    std::vector<Product> products;
    std::vector<Product> soldProducts;
  public:
    void addProductForSale();
    void viewProducts();
    void viewSoldProducts();
    bool overview();
    bool closeBid(Product p);
    bool openBid(Product p);
};

class Buyer: public User{
  private:
    std::vector<Product> purchases;
  public:
    void browseProducts();
    void addBidToProduct();
    void viewPurchases();
    void sendMessage(User to);
    bool overview();
};

#endif