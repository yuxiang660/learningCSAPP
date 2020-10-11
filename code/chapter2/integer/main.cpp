#include <iostream>
#include <limits>

int main() {
   std::cout << "Integer in Computer" << std::endl;

   auto max_uint32_t = std::numeric_limits<uint32_t>::max();
   std::cout << "max uint32_t: " << max_uint32_t << std::endl;

   auto min_int32_t = std::numeric_limits<int32_t>::min();
   std::cout << "min int32_t: " << min_int32_t << std::endl;

   uint32_t base_uint32_t = 1;
   auto ret = base_uint32_t + min_int32_t;
   std::cout << "cast int32_t to uint32_t: " << static_cast<uint32_t>(min_int32_t) << std::endl;
   std::cout << "uint32_t plus int32_t: " << ret << std::endl;

   return 0;
}