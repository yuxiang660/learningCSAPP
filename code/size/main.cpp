#include <iostream>
#include <typeinfo>

template<typename T>
void printTypeSize(T data) {
   std::cout << "Size of type " << typeid(T).name() << " is " << sizeof(T) << std::endl;
}

int main() {
   std::cout << "--- Size of Each Types ---" << std::endl;

   printTypeSize(char(0));
   printTypeSize((unsigned char)(0));
   printTypeSize(short(0));
   printTypeSize((unsigned short)(0));
   printTypeSize(int(0));
   printTypeSize((unsigned)(0));
   printTypeSize((unsigned int)(0));
   printTypeSize(long(0));
   printTypeSize((unsigned long)(0));
   printTypeSize((long long)(0));
   printTypeSize((unsigned long long)(0));
   printTypeSize(int32_t(0));
   printTypeSize(uint32_t(0));
   printTypeSize(int64_t(0));
   printTypeSize(uint64_t(0));
   printTypeSize((char *)(0));
   printTypeSize(float(0));
   printTypeSize(double(0));

   return 0;
}
