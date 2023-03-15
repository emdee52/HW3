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