#include "Product.h"

int Product::count = 0; // static member initialization

void Product::addBid(int uid, double bid) {
  bids[uid] = bid;
}

std::map<int, double> Product::getHighestBid(){
  std::map<int, double> highestBid;
  double maxBid = price_;
  int uid;

  for (const auto &[key, value] : bids){
    if (maxBid <= value){
      maxBid = value;
      uid = key;
    }
  }
  if (uid == -1)
    std::cout << "No current bids, base price is $" << maxBid << std::endl;
  else
    std::cout << "Highest bid is $" << maxBid << " by User " << uid << std::endl;

  highestBid[uid] = maxBid;
  return highestBid;
}

void Product::viewBids(){
  for (const auto &[key, value] : bids)
    std::cout << "bids[" << key << "] = " << value << std::endl;
}

Product* Product::productFactory(ProductCategory pc, double price, std::string name, std::string quality){
  switch(pc){
    case ProductCategory::Vehicle:
      return new Vehicle(price, name, quality);
    case ProductCategory::Furniture:
      return new Furniture(price, name, quality);
    case ProductCategory::Tool:
          return new Tool(price, name, quality);
    case ProductCategory::Book:
      return new Book(price, name, quality);
    case ProductCategory::Clothes:
      return new Clothes(price, name, quality);
    default:
      return new Product();
  }
}

void Product::setBidStatus(bool status) {
  this->openBids = status;
}