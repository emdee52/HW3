#ifndef _USER_H_
#define _USER_H_
#include <iostream>
#include <vector>
#include "Product.h"
#include <string>
#include <iostream>

// struct Message;
class User;

enum class UserType{SELLER, BUYER, USER};

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
    
    void setBalance(double bal) { balance_ = bal; }
    void setId(int id) { id_ = id; }
    void setName(std::string name) { name_ = name; }
    void setAddress(std::string addy) { address_ = addy; }
    void setPhone(std::string phone) { phone_ = phone; }
    void addMessage(Message message) { messages_.push_back(message); }

    void updateInfo();

    double getBalance() const { return balance_; }
    int getId() const { return id_; }
    std::string getName() const { return name_; }
    std::string getAddress() const { return address_; }
    std::string getPhone() const { return phone_; }

    bool printMessages();
    void viewMessages();
    void viewBalance();
    void respond(int index);

    virtual bool overview(){};
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

    void addProductForSale();
    void viewProducts();
    void viewSoldProducts();
    bool overview();
    void assignBidStatus();
    bool closeBid(Product &p);
    bool openBid(Product &p);
    void menu();
};

class Buyer: public User{
  private:
    std::vector<Product> purchases;
  public:
    Buyer(){ type = UserType::BUYER; }
    Buyer(double balance, std::string name, std::string addy, std::string phone) : User(balance, name, addy, phone){
      type = UserType::BUYER;
    }

    void browseProducts();
    void addBidToProduct();
    void viewPurchases();
    void sendMessage(User &to);
    bool overview();
    void menu();
};

#endif