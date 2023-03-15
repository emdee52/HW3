#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <iostream>
#include <map>

enum class ProductCategory {Vehicle, Furniture, Book, Tool, Clothes, Product}; 

class Product{
  protected:
    int id_;
    double price_;
    std::map<int, double> bids;
    std::string name_;
    std::string quality_;
    ProductCategory category;
    bool openBids;
    static int count;
  public:
    Product(): id_(++count), price_(0), name_(""), quality_("New"), category(ProductCategory::Product), openBids(true){
      addBid(-1, price_);
    }

    Product(double price, std::string name, std::string quality) : id_(++count), price_(price), name_(name), quality_(quality), category(ProductCategory::Product), openBids(true){}

    // Setters
    void setPrice(double price) { price_ = price; }
    void setId(int id) { id_ = id; }
    void setQuality(std::string quality) { quality_ =  quality; }
    void setName(std::string name) { name_ = name; }
    void setBidStatus(bool status);

    void addBid(int uid, double bid); // adds a bid to the product
    std::map<int, double> getHighestBid(); // returns a singular map of the current highest bid along with user id
    void viewBids(); // display current bids on the product

    // Getters
    bool getBidStatus() const { return openBids; }
    double getPrice() const { return price_; }
    int getId() const { return id_; }
    std::string getQuality() const { return quality_; }
    std::string getName() const { return name_; }
    ProductCategory getCategory() const { return category; }

    static Product* productFactory(ProductCategory pc, double bid, std::string name, std::string quality); // factory pattern to generate products
};

class Vehicle: public Product{
  public:
    Vehicle(double price, std::string name, std::string quality) : Product(price, name, quality){
      category = ProductCategory::Vehicle;
      // std::cout << "Vehicle" << std::endl;
    }
};

class Furniture: public Product{
  public:
    Furniture(double price, std::string name, std::string quality) : Product(price, name, quality){
      category = ProductCategory::Furniture;
      // std::cout << "Furniture" << std::endl;
    }
};

class Book: public Product{
  public:
    Book(double price, std::string name, std::string quality) : Product(price, name, quality){
      category = ProductCategory::Book;
      // std::cout << "Book" << std::endl;
    }
};

class Tool: public Product{
  public:
    Tool(double price, std::string name, std::string quality) : Product(price, name, quality){
      category = ProductCategory::Tool;
      // std::cout << "Tool" << std::endl;
    }
};

class Clothes: public Product{
  public:
    Clothes(double price, std::string name, std::string quality) : Product(price, name, quality){
      category = ProductCategory::Clothes;
      // std::cout << "Clothes" << std::endl;
    }
};

#endif