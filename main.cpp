/*
Name: Md Mahmud
How to run: 
  (1) make main
  (2) ./main

How it works: You create an account as a buyer or seller, and they will each have their respective
commands they can perform. To navigate within the menu, you will be presented with a list of numerical
options which you can type the digit to select the option you want to pick.

*/
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include "Driver.h"

int main() {
  Driver & ebay = Driver::getInstance();
  ebay.run();
}