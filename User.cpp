#include "User.h"

void createMessage(Message &m, std::string data, User * from, User * to) {
  m.data = data;
  m.from = from;
  m.to = to;
}

Product * productSetup(ProductCategory category) {
  int option;
  double price;
  std::string name;
  std::string quality = "";

  std::cout << "Choose a product NAME: " << std::endl;
  std::cin.ignore();
  std::getline(std::cin, name);

  std::cout << "Choose a product PRICE: " << std::endl;
  std::cin >> price;

  while (quality == "") {
    std::cout << "Choose a product QUALITY: " << std::endl;
    std::cout << "  (1) New" << std::endl;
    std::cout << "  (2) Used-VeryGood" << std::endl;
    std::cout << "  (3) Used-Good" << std::endl;
    std::cout << "  (4) Used-Okay" << std::endl;
    std::cin >> option;

    switch (option)
    {
    case 1: {
      quality = "New";
      break;
    }
    case 2: {
      quality = "Used-VeryGood";
      break;
    }
    case 3: {
      quality = "Used-Good";
      break;
    }
    case 4: {
      quality = "Used-Okay";
      break;
    }  
    default:
      break;
    }
  }

  return Product::productFactory(category, price, name, quality);
}

int User::count = 0;

bool User::printMessages() {

  if (messages_.size() == 0){
    std::cout << "[INFO] No Messages" << std::endl;
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

void User::viewBalance(){
  std::cout << "[INFO] Balance: " << balance_ << std::endl;
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

void User::updateInfo(){
  while (true)
  {
    int option;

    std::cout << "=========USER INFO=========" << std::endl;
    std::cout << "(1) Change name" << std::endl;
    std::cout << "(2) Change phone number" << std::endl;
    std::cout << "(3) Change address" << std::endl;
    std::cout << "(0) Exit" << std::endl;
    std::cout << "[PICK AN OPTION]" << std::endl;
   
    std::cin >> option;
    switch (option)
    {
    case 1: {
      std::cout << "Changing name: What would you like your new name to be?" << std::endl;
      std::cin.ignore();
      std::getline(std::cin, name_);
      break;
    }
    case 2:
      std::cout << "Changing number: What would you like your new phone number to be?" << std::endl;
      std::cin.ignore();
      std::getline(std::cin, phone_);
      break;
    case 3:
      std::cout << "Changing address: What would you like your new address to be?" << std::endl;
      std::cin.ignore();
      std::getline(std::cin, address_);
      break;    
    default:
      return;
    }
  }
}

Product * Seller::addProductForSale(){
  int option;
  ProductCategory category = ProductCategory::Product;
  Product * listing;


  while (category == ProductCategory::Product){
    std::cout << "=========LISTING=========" <<std::endl;
    std::cout << "(1) Vehicle" << std::endl;
    std::cout << "(2) Furniture" << std::endl;
    std::cout << "(3) Tool" << std::endl;
    std::cout << "(4) Book" << std::endl;
    std::cout << "(5) Clothes" << std::endl;
    std::cout << "(0) Exit" << std::endl;
    std::cout << "[CHOOSE A CATEGORY]" << std::endl;
    std::cin >> option;

    switch (option)
    {
    case 1: {
      category = ProductCategory::Vehicle;
      break;
    }
    case 2:{
      category = ProductCategory::Furniture;
      break;
    }
    case 3:{
      category = ProductCategory::Tool;
      break;
    }
    case 4:{
      category = ProductCategory::Book;
      break;
    }
    case 5:{
      category = ProductCategory::Clothes;
      break;
    }
    default:
      break;
    }
  }
  listing = productSetup(category);
  
  products.push_back(listing);

  return listing;
}

void Seller::viewProducts(){
  std::string strStatus = "";
  bool status;
  std::cout << "Products for Sale: " << std::endl;

  if (products.size() < 1) {
    std::cout << "  [INFO] No products for sale" << std::endl;
    return;
  }

  for (int i = 0; i < products.size(); i++){
    status = products[i]->getBidStatus();

    if (status)
      strStatus = "Open";
    else
      strStatus = "Closed";

    std::cout << "   (" << i + 1 << ") " << products[i]->getName() << ": Price[$" << products[i]->getPrice() << "], " << "Quality[" << products[i]->getQuality() << "], " << "Status[" << strStatus << "]" << std::endl;
  }
}

void Seller::viewSoldProducts(){
  std::cout << "Previously sold products: " << std::endl;

  if (soldProducts.size() < 1) {
    std::cout << "  [INFO] No sold products" << std::endl;
    return;
  }

  for (int i = 0; i < soldProducts.size(); i++)
    std::cout << "   (" << i + 1 << ") " << soldProducts[i]->getName() << ": Price[$" << soldProducts[i]->getPrice() << "], " << "Quality[" << soldProducts[i]->getQuality() << "]" << std::endl;
}

void Seller::overview(){
  std::cout << "=========OVERVIEW=========" << std::endl;
  std::cout << "Name:    " << this->getName() << std::endl;
  std::cout << "Id:      " << this->getId() << std::endl;
  std::cout << "Address: " << this->getAddress() << std::endl;
  std::cout << "Phone:   " << this->getPhone() << std::endl;
  std::cout << "Balance: " << this->getBalance() << std::endl << std::endl;
  viewProducts();
  viewSoldProducts();
}

void Seller::assignBidStatus() {
  int option;
  std::cout << "=========PRODUCTS=========" << std::endl;
  viewProducts();

  if (products.size() < 1) {
    std::cout << "[PLEASE LIST A PRODUCT FIRST]" << std::endl;
    return;
  }

  std::cout << "[CHOOSE A PRODUCT TO OPEN/CLOSE BIDS]" << std::endl;
  std::cin >> option;

  Product *p = products[option - 1];

  if (p->getBidStatus()) {
    p->setBidStatus(false);
    std::cout << "[INFO] Bidding closed for Product "  << p->getId() << ": " << p->getName() << std::endl;
  }
  else {
    p->setBidStatus(true);
    std::cout << "[INFO] Bidding open for Product "  << p->getId() << ": " << p->getName() << std::endl;
  }
}

void Seller::menu(){
  int option;

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
        addProductForSale();
        break;
      case 2: 
        viewMessages();
        break;
      case 3:
        viewBalance();
        break;
      case 4:
        updateInfo();
        break;
      case 5:
        overview();
        break;
      case 6:
        assignBidStatus();
        break;
      default:
        break;
    }
  }
}

void Buyer::addBidToProduct(int pid, double bid){
  bids[pid] = bid;
}

void Buyer::viewPurchases(){
  std::cout << "Purchased products: " << std::endl;

  if (purchases.size() < 1) {
    std::cout << "  [INFO] No purchases" << std::endl;
    return;
  }

  for (int i = 0; i < purchases.size(); i++)
    std::cout << "   (" << i + 1 << ") " << purchases[i]->getName() << ": Price[$" << purchases[i]->getPrice() << "], " << "Quality[" << purchases[i]->getQuality() << "]" << std::endl;
}

void Buyer::sendMessage(User &to){
  Message m;
  std::string message;
  std::cout << "Send message to seller: ";
  std::cin >> message;
  createMessage(m, message, this, &to);

  to.addMessage(m);
  this->addMessage(m);
}

void Buyer::overview(){
  std::cout << "Bids placed: " << std::endl;

  if (bids.size() < 1) {
    std::cout << "  [INFO] No bids" << std::endl;
    return;
  }

  for(const auto& elem : bids)
  {
    std::cout << "Bid $" << elem.second << " on Product" << elem.first << "\n";
  }
  
  for (int i = 0; i < purchases.size(); i++)
    std::cout << "   (" << i + 1 << ") " << purchases[i]->getName() << ": Price[$" << purchases[i]->getPrice() << "], " << "Quality[" << purchases[i]->getQuality() << "]" << std::endl;
}

void Buyer::menu(){
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
    break;
  case 2: 
    viewMessages();
    break;
  case 3:
    viewBalance();
    break;
  case 4:
    updateInfo();
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  
  default:
    break;
  }
}

User * User::userFactory(UserType type, double balance, std::string name, std::string addy, std::string phone){
  switch(type){
    case UserType::BUYER:
      return new Buyer(balance, name, addy, phone);
    case UserType::SELLER:
      return new Seller(balance, name, addy, phone);
    default:
      return new User(balance, name, addy, phone);
  }
}