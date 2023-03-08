#include "User.h"
#include "Product.h"

void User::setBalance(double bal){}
void User::setId(int id){}
void User::setName(std::string name){}
void User::setAddress(std::string addy){}
void User::setPhone(std::string phone){}
void User::addMessage(std::string message){}

double User::getBalance(){}
int User::getId(){}
std::string User::getName(){}
std::string User::getAddress(){}
std::string User::getPhone(){}
std::vector<std::string> User::viewMessages(){}
void User::respond(User to){}

void Seller::addProductForSale(){}
void Seller::viewProducts(){}
void Seller::viewSoldProducts(){}
bool Seller::overview(){}
bool Seller::closeBid(Product p){}
bool Seller::openBid(Product p){}

void Buyer::browseProducts(){}
void Buyer::addBidToProduct(){}
void Buyer::viewPurchases(){}
void Buyer::sendMessage(User to){}
bool Buyer::overview(){}