#include <iostream>
#include <vector>
#include "Driver.h"
#include "User.h"
#include <typeinfo>
#include <fstream>
#include <string.h>

// helper function to split csv lines using the comma delimiter
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

// print operator overload for UserType enum
std::ostream& operator<<(std::ostream& os, UserType type)
{
  switch(type)
  {
    case UserType::SELLER : return os << "SELLER" ;
    case UserType::BUYER : return os << "BUYER" ;
    case UserType::USER : return os << "USER" ;
    default: return os << "UserType{" << int(type) << '}' ;
  }
}

// print operator overload for ProductCategory enum
std::ostream& operator<< ( std::ostream& os, ProductCategory category )
{
  switch(category)
  {
    case ProductCategory::Vehicle : return os << "Vehicle" ;
    case ProductCategory::Furniture : return os << "Furniture" ;
    case ProductCategory::Book : return os << "Book" ;
    case ProductCategory::Tool : return os << "Tool" ;
    case ProductCategory::Clothes : return os << "Clothes" ;
    case ProductCategory::Product : return os << "Product" ;
    default: return os << "ProductCategory{" << int(category) << '}' ;
  }
}

void Driver::run(){
  std::ofstream outfile;
  std::string line;

  readUsers();
  readHistoricalProducts();
  User * user = initializeUser();

  // if(user->getType() ==  UserType::SELLER)
  //   line = "seller," + user->getName() + "," + user->getAddress() + "," + user->getPhone();
  // else if (user->getType() ==  UserType::BUYER)
  //   line = "seller," + user->getName() + "," + user->getAddress() + "," + user->getPhone();

  // outfile.open("users.csv", std::ios_base::app);
  // outfile << std::endl;
  // outfile << line; 

  viewUsers();
  menu(user);
}

User * userSetup(UserType type) {
  int option;
  double balance;
  std::string name = "";
  std::string addy = "";
  std::string phone = "";

  std::cout << "=========ACCOUNT=========" << std::endl;
  std::cout << "Input NAME: ";
  std::cin.ignore();
  std::getline(std::cin, name);


  std::cout << "Input ADDRESS: ";
  std::getline(std::cin, addy);


  std::cout << "Input PHONE: ";
  std::getline(std::cin, phone);


  std::cout << "Input BALANCE: ";
  std::cin >> balance;

  return User::userFactory(type, balance, name, addy, phone);
}

User * Driver::initializeUser(){
  User * user;
  int option;

  std::cout << "=========ACCOUNT=========" << std::endl;
  std::cout << "(1) Buyer" << std::endl;
  std::cout << "(2) Seller" << std::endl;
  std::cout << "[PICK AN ACCOUNT TYPE]" << std::endl;
  std::cin >>  option;

  while (true) {
    switch (option) {
      case 1: {
        user = userSetup(UserType::BUYER);
        addUser(user);
        return user;
      }
      case 2: {
        user = userSetup(UserType::SELLER);
        addUser(user);
        return user;
      }
      default: {
        break;
      }
    }
  }
}

void Driver::viewActiveProducts(Buyer * buya){
  int option;

  std::cout << "Active products for Sale: " << std::endl;
  for (int i = 0; i < activeProducts.size(); i++)
  {
    if (activeProducts[i]->getBidStatus()){
      std::cout << "   (" << i + 1 << ") " << activeProducts[i]->getName() 
      << ": Price[$" << activeProducts[i]->getPrice() << "], " 
      << "Quality[" << activeProducts[i]->getQuality()
      << std::endl;
    }
  }
  std::cout << "(0) Exit" << std::endl;
  std::cout << "[PICK A PRODUCT TO BID OR EXIT]" << std::endl;
  std::cin >> option;

  if (!activeProducts[option - 1]->getBidStatus()){
    std::cout << "[INFO] Bidding on this item is closed" << std::endl;
    return;
  }

  while (true)
  {
    double bid;
    if (option == 0)
      return;
    else {
      std::cout << "Current highest bid: "<< activeProducts[option - 1]->getHighestBid().begin()->second << std::endl;
      std::cout << "[Choose a bidding price]" << std::endl;
      std::cin >> bid;
      if (bid < activeProducts[option - 1]->getHighestBid().begin()->second){
        int op;
        std::cout << "[INFO] Your bid is lower than the highest bid" << std::endl;
        std::cout << "[DO YOU WISH TO BID AGAIN?] (1) Yes (2) No" << std::endl;
        std::cin >> op;

        if (op == 2)
          return;

        continue;
      }

      if (buya->getBalance() < bid){
        int op;
        std::cout << "[INFO] Your balance is lower than your bid" << std::endl;
        std::cout << "[DO YOU WISH TO BID AGAIN?] (1) Yes (2) No" << std::endl;
        std::cin >> op;
        if (op == 2)
          return;

        continue;
      }

      if (activeProducts[option - 1]->getPrice() > bid){
        int op;
        std::cout << "[INFO] Your bid is lower than the base price" << std::endl;
        std::cout << "[DO YOU WISH TO BID AGAIN?] (1) Yes (2) No" << std::endl;
        std::cin >> op;
        if (op == 2)
          return;

        continue;
      }

      activeProducts[option - 1]->addBid(buya->getId(), bid);
      buya->addBidToProduct(activeProducts[option - 1]->getId(), bid);
      break;
    }
  }
}

void Driver::menu(User * user){
  int option = 99;

  if (user->getType() == UserType::SELLER){
    Seller * sella = static_cast<Seller *>(user);
    while (option != 0) {
      std::cout << "=========OPTIONS=========" <<std::endl;
      std::cout << "(1) List product for sale" << std::endl;
      std::cout << "(2) Check messages" << std::endl;
      std::cout << "(3) Check balance" << std::endl;
      std::cout << "(4) Update user information" << std::endl;
      std::cout << "(5) Get overview" << std::endl;
      std::cout << "(6) Open/close bids" << std::endl;
      std::cout << "(0) Exit" << std::endl;
      std::cout << "[PICK AN OPTION]" << std::endl;
      std::cin >> option;
      switch (option){
        case 1: {
          Product * p = sella->addProductForSale();
          std::string category;
          addActiveProducts(p);
          std::ofstream outfile;
          outfile.open("products.csv", std::ios_base::app); 
          if (p->getCategory() == ProductCategory::Book) category = "book";
          else if (p->getCategory() == ProductCategory::Clothes) category = "clothes";
          else if (p->getCategory() == ProductCategory::Vehicle) category = "vehicle";
          else if (p->getCategory() == ProductCategory::Furniture) category = "furniture";
          else if (p->getCategory() == ProductCategory::Tool) category = "tool";
          std::string line = std::to_string(p->getId()) + "," + std::to_string((int) p->getPrice()) + "," + category + "," + p->getName() + "," + p->getQuality();
          outfile << std::endl;
          outfile << line; 

          std::cout << p->getName() << " listed: Price[$" << p->getPrice() << "], " << "Quality[" << p->getQuality() << "]" << std::endl;
          break;
        }

        case 2: 
          sella->viewMessages();
          break;
        case 3:
          sella->viewBalance();
          break;
        case 4:
          sella->updateInfo();
          break;
        case 5:
          sella->overview();
          break;
        case 6: {
          if (sella->getProducts().size() < 1) {
            std::cout << "[PLEASE LIST A PRODUCT FIRST]" << std::endl;
            break;
          }
          std::map<bool, Product *> sold;
          sold = sella->assignBidStatus();
          if (sold.begin()->first){
            Product * p = sold.begin()->second;
            sella->productSold(p);
            std::cout << "Product " << p->getName() << " sold to Buyer " << p->getHighestBid().begin()->first << " for $" << p->getHighestBid().begin()->second << std::endl;
          }
          break;
        }
        default:
          break;
      }
    }
  }
  else if (user->getType() == UserType::BUYER){
    Buyer * buya = static_cast<Buyer *>(user);
    while (option != 0) {
      int option;
      std::cout << "=========OPTIONS=========" <<std::endl;
      std::cout << "(1) View products for sale" << std::endl;
      std::cout << "(2) Check messages" << std::endl;
      std::cout << "(3) Check balance" << std::endl;
      std::cout << "(4) Update user information" << std::endl;
      std::cout << "(5) Get overview" << std::endl;
      std::cout << "(6) View purchases" << std::endl;
      std::cout << "(0) Exit" << std::endl;
      std::cout << "[PICK AN OPTION]" << std::endl;

      std::cin >> option;
      switch (option)
      {
      case 1:
        viewActiveProducts(buya);
        break;
      case 2: 
        buya->viewMessages();
        break;
      case 3:
        buya->viewBalance();
        break;
      case 4:
        buya->updateInfo();
        break;
      case 5:
        buya->overview();
        break;
      case 6:
        buya->viewPurchases();
        break;
      case 7:
        break;
      
      default:
        break;
      }
    }
  }
}

void Driver::viewUsers(){
  std::cout << "Current users in the system: " << std::endl;

  if (users.size() < 1){
    std::cout << "[INFO] No users in the system" << std::endl;
    return;
  }

  for (int i = 0; i < users.size(); i++){
    std::cout << "  (" << i << ") " 
    << users[i]->getType() << " "
    << users[i]->getName() << ": " 
    << "Balance[$" << users[i]->getBalance() << "], "
    << "Address[" << users[i]->getAddress() << "], "
    << "Phone["   << users[i]->getPhone() << "] "
    << std::endl;
  }
}

void Driver::readUsers(){
  std::vector<std::string> s;
  std::ifstream intfile("users.csv");
  std::string line;

  while (std::getline(intfile, line)){
    User * u;
    s = splitter(line);
    // std::cout << line << std::endl;
    // std::cout << s[0] << std::endl;
    std::string type = s[0];
    std::string name = s[1];
    double balance = std::stod(s[2]);
    std::string addy = s[3];
    std::string phone = s[4];

    if (type == "buyer")
      u = User::userFactory(UserType::BUYER, balance, name, addy, phone);
    else if (type == "seller")
      u = User::userFactory(UserType::SELLER, balance, name, addy, phone);
    
    addUser(u);
  }
}

void Driver::readHistoricalProducts(){
  std::vector<std::string> s;
  std::ifstream intfile("products.csv");
  std::string line;

  while (std::getline(intfile, line)){
    Product * p;
    s = splitter(line);
    int buyerId = std::stoi(s[0]);
    double bid = std::stod(s[1]);
    std::string type = s[2];
    std::string name = s[3];
    std::string quality = s[4];

    if (type == "book")
      p = Product::productFactory(ProductCategory::Book, bid, name, quality);
    else if (type == "clothes")
      p = Product::productFactory(ProductCategory::Clothes, bid, name, quality);
    else if (type == "vehicle")
      p = Product::productFactory(ProductCategory::Vehicle, bid, name, quality);
    else if (type == "furniture")
      p = Product::productFactory(ProductCategory::Furniture, bid, name, quality);
    else if (type == "tool")
      p = Product::productFactory(ProductCategory::Tool, bid, name, quality);
    
    addFinishedBid(buyerId, p);
  }
}
