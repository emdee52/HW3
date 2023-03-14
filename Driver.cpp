#include <iostream>
#include <vector>
#include "Driver.h"
#include "User.h"
#include <typeinfo>

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

void Driver::saveBidInfo(Product p){}

void Driver::run(){
  User * user = initializeUser();
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

void Driver::viewActiveProducts(){
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
}


void Driver::addBids(Product p){}

std::vector<Product> Driver::getActiveProducts(){}
std::vector<Product> Driver::getBids(){}
std::vector<User> Driver::getUsers(){}

void Driver::menu(User * user){
  int option;

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
        case 1:
          addActiveProducts(sella->addProductForSale());
          break;
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
        case 6:
          sella->assignBidStatus();
          break;
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
        viewActiveProducts();
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