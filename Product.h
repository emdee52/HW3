#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <iostream>
#include <map>

enum class ProductCategory {Vehicle, Furniture, Book, Tool, Clothes, Product}; 

class Product{
  protected:
    int id_;
    double price_;
    double maxBid_;
    std::map<int, double> bids;
    std::string name_;
    std::string quality_;
    ProductCategory category;
    bool openBids;
    static int count;
  public:
    Product(): id_(++count), price_(0), name_(""), quality_("New"), category(ProductCategory::Product), openBids(true){}

    Product(double price, std::string name, std::string quality) : id_(++count), price_(price), name_(name), quality_(quality), category(ProductCategory::Product), openBids(true){}

    void setPrice(double price) { price_ = price; }
    void setId(int id) { id_ = id; }
    void setQuality(std::string quality) { quality_ =  quality; }
    void setName(std::string name) { name_ = name; }
    void setBidStatus(bool status);

    void addBid(int uid, double bid);
    std::map<int, double> getHighestBid();
    void viewBids();

    bool getBidStatus() const { return openBids; }
    double getPrice() const { return price_; }
    int getId() const { return id_; }
    std::string getQuality() const { return quality_; }
    std::string getName() const { return name_; }

    static Product* productFactory(ProductCategory pc, double bid, std::string name, std::string quality);
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