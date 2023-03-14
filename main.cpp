#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include "Driver.h"


std::vector<std::string> splitter(std::string str){
  std::vector<std::string> v;
  std::string curr = ""; 
  
  for(int i = 0; i < str.size(); i++){
    if(str[i] == ','){
      if(curr != ""){
        v.push_back(curr);
        curr = "";
      } 
      continue;
    }
    curr += str[i];
  }
  if(curr.size() != 0)
    v.push_back(curr);
  return v;
}

int main() {
  // Driver& driver = Driver::getInstance();
  // std::vector<std::string> s;
  // std::ifstream intfile("products.csv");
  // std::string line;
  // while (intfile >> line){
  //   Product * p;
  //   s = splitter(line);
  //   int id = std::stoi(s[0]);
  //   int buyer = std::stoi(s[1]);
  //   double bid = std::stod(s[2]);
  //   int seller = std::stoi(s[3]);
  //   std::string type = s[4];
  //   std::string name = s[5];
  //   std::string quality = s[6];

  //   if (type == "book")
  //     p = Product::productFactory(ProductCategory::Book, id, bid, name, quality);
  //   else if (type == "clothes")
  //     p = Product::productFactory(ProductCategory::Clothes, id, bid, name, quality);
  //   else if (type == "vehicle")
  //     p = Product::productFactory(ProductCategory::Vehicle, id, bid, name, quality);
  //   else if (type == "furniture")
  //     p = Product::productFactory(ProductCategory::Furniture, id, bid, name, quality);
  //   else if (type == "tool")
  //     p = Product::productFactory(ProductCategory::Tool, id, bid, name, quality);
    
  //   driver.addFinishedBid(id, p);
  // }
  // std::map<int, Product *> m = driver.getFinishedBids();
  // for (const auto& x : m) { // prints out the map (id : productName)
  //     std::cout << x.first << ": " << x.second->getName() << "\n";
  // }
  Driver & ebay = Driver::getInstance();
  ebay.run();
  
  // Seller sella(0, "JohnSela", "Johnstown", "303000303");
  // Buyer buya(0, "BobBuya", "Bobertstown", "720000720");
  // sella.updateInfo();
  // sella.printReport();
  // sella.menu();
  // buya.sendMessage(sella);
  // sella.viewMessages();
  // sella.printReport();
  // buya.printReport();
  // sella.printMessages();
  // buya.printMessages();
}