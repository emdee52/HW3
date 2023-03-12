#include "User.h"

void createMessage(Message &m, std::string data, int id) {
  m.data = data;
  m.fromId = id;
}

int User::count = 0;

void User::printReport(){
  std::cout << "Name:    " << name_ << std::endl;
  std::cout << "Id:      " << id_ << std::endl;
  std::cout << "Address: " << address_ << std::endl;
  std::cout << "Phone:   " << phone_ << std::endl;
  std::cout << "Balance: " << balance_<< std::endl << std::endl;
}

bool User::printMessages() {

  if (messages_.size() == 0){
    std::cout << "No messages" << std::endl;
    return false;
  }
  std::cout << "=========MESSAGES=========" << std::endl;
  for (int i = 0; i < messages_.size(); i++){
    std::cout << "(" << i << ") From User " << messages_[i].fromId << ": " << messages_[i].data << std::endl;
  }
  return true;
}

void User::viewMessages(){
  int response;
  bool hasMessage;
  hasMessage = printMessages();

  if (hasMessage){
    std::cout << "Respond to messages? 1:(yes) 2:(no)" << std::endl;
    std::cin >> response;
    
    while(response == 1){
      int option;
      std::cout << "Select message to respond to: " ;
      std::cin >> option;
    }
  }
}

void User::respond(){
  std::string message;
  std::cout << "Responding to message: " << std::endl;
  std::cin >> message;
}

void Seller::addProductForSale(){}
void Seller::viewProducts(){}
void Seller::viewSoldProducts(){}
bool Seller::overview(){}
bool Seller::closeBid(Product p){}
bool Seller::openBid(Product p){}

void Buyer::browseProducts(){}
void Buyer::addBidToProduct(){}
void Buyer::viewPurchases(){}

void Buyer::sendMessage(User &to){
  Message m;
  std::string message;
  std::cout << "Send message to buyer: ";
  std::cin >> message;
  createMessage(m, message, to.getId());

  to.addMessage(m);
  this->addMessage(m);
}

bool Buyer::overview(){}