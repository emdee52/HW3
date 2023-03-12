#include "User.h"

void createMessage(Message &m, std::string data, User * from, User * to) {
  m.data = data;
  m.from = from;
  m.to = to;
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
    if (messages_[i].from->getId() != this->id_)
      std::cout << "(" << i + 1 << ") From " << messages_[i].from->getName() << ": " << messages_[i].data << std::endl;
    else
      std::cout << "(" << i + 1 << ") To " << messages_[i].to->getName() << ": " << messages_[i].data << std::endl;
  }
  std::cout << "(0) Exit" << std::endl;
  return true;
}

void User::viewMessages(){
  bool hasMessage;
  hasMessage = printMessages();

  if (hasMessage){
    while(true){
      int option;
      std::cout << "Choose a digit to respond to or exit: " ;
      std::cin >> option;
      if (option == 0)
        break;
      else if (option > messages_.size())
        continue;
      respond(option - 1);
      printMessages();
    }
  }
}

void User::respond(int index){
  Message m;
  std::string message;
  User * to = messages_[index].from;
  
  if (to->getId() == this->getId()) {
    std::cout << "[INFO] Cannot respond to own message, choose a different message" << std::endl;
    return;
  }
    
  std::cout << "Responding to " << to->getName() << "'s message (" << index + 1 << "): ";
  std::cin >> message;
  createMessage(m, message, this, to);

  to->addMessage(m);
  this->addMessage(m);  
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
  std::cout << "Send message to seller: ";
  std::cin >> message;
  createMessage(m, message, this, &to);

  to.addMessage(m);
  this->addMessage(m);
}

bool Buyer::overview(){}