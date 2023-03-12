#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <iostream>

enum class ProductCategory {Vehicle, Furniture, Book, Tool, Clothes}; 

class Product{
  protected:
    int id_;
    double price_;
    std::string name_;
    std::string quality_;

  public:
    Product(){}

    Product(int id, double price, std::string name, std::string quality) : id_(id), price_(price), name_(name), quality_(quality){}

    void setPrice(double price) { price_ = price; }
    void setId(int id) { id_ = id; }
    void setQuality(std::string quality) { quality_ =  quality; }
    void setName(std::string name) { name_ = name; }

    double getPrice();
    int getId();
    std::string getQuality();
    std::string getName(){ return name_; }
    static Product* productFactory(ProductCategory pc, int id, double bid, std::string name, std::string quality);
};

class Vehicle: public Product{
  private:
    std::string model;
    std::string make;
    int year;
  public:
    Vehicle(int id, double price, std::string name, std::string quality) : Product(id, price, name, quality){
      // std::cout << "Vehicle" << std::endl;
    }
    std::string getModel();
    std::string getMake();
    int getYear();
};

class Furniture: public Product{
  private:
    std::string size;
  public:
    Furniture(int id, double price, std::string name, std::string quality) : Product(id, price, name, quality){
      // std::cout << "Furniture" << std::endl;
    }
    std::string getSize();
};

class Book: public Product{
  private:
    std::string genre;
    std::string author;
  public:
    Book(int id, double price, std::string name, std::string quality) : Product(id, price, name, quality){
      // std::cout << "Book" << std::endl;
    }
    std::string getGenre();
    std::string getAuthor();
};

class Tool: public Product{
  private:
    std::string type;
  public:
    Tool(int id, double price, std::string name, std::string quality) : Product(id, price, name, quality){
      // std::cout << "Tool" << std::endl;
    }
    std::string getType();
};

class Clothes: public Product{
  private:
    std::string type;
  public:
    Clothes(int id, double price, std::string name, std::string quality) : Product(id, price, name, quality){
      // std::cout << "Clothes" << std::endl;
    }
    std::string getType();
};

#endif