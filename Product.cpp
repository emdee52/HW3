#include "Product.h"

void Product::setPrice(double price){}
void Product::setId(int id){}
void Product::setQuality(std::string quality){}
void Product::setName(std::string name){}

double Product::getPrice(){}
int Product::getId(){}
std::string Product::getQuality(){}

Product* Product::productFactory(ProductCategory pc, int id, double price, std::string name, std::string quality){
  switch(pc){
    case ProductCategory::Vehicle:
      return new Vehicle(id, price, name, quality);
    case ProductCategory::Furniture:
      return new Furniture(id, price, name, quality);
    case ProductCategory::Tool:
          return new Tool(id, price, name, quality);
    case ProductCategory::Book:
      return new Book(id, price, name, quality);
    case ProductCategory::Clothes:
      return new Clothes(id, price, name, quality);
    default:
      return new Product();
  }
}

std::string Vehicle::getModel(){}
std::string Vehicle::getMake(){}
int Vehicle::getYear(){}

std::string Furniture::getSize(){}

std::string Book::getGenre(){}
std::string Book::getAuthor(){}

std::string Tool::getType(){}

std::string Clothes::getType(){}