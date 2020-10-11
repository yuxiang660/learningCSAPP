#include <iostream>
#include <limits>

// int - 4 bytes
// char - 1 byte
// double - 8 bytes
struct type1 {
   int a;
   char b;
   double c;
};

struct type2 {
   char b;
   double c;
   int a;
};

struct type3 {
   char b;
   double c;
   int a;
}__attribute__ ((aligned (16)));

int main() {
   std::cout << "Size of Struct" << std::endl;

   std::cout << "size of type1: " << sizeof(type1) << std::endl;
   std::cout << "size of type2: " << sizeof(type2) << std::endl;
   std::cout << "size of type3: " << sizeof(type3) << std::endl;

   return 0;
}