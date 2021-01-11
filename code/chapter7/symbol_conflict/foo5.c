#include <stdio.h>
void f(void);

int x = 15213;
int y = 15212;

int main()
{
   f();
   printf("double size: %lu, int size: %lu \n", sizeof(double), sizeof(int));
   printf("address of x: %p, address of y: %p \n", &x, &y);
   printf("x = 0x%x, y = 0x%x \n", x, y);
   printf("x = %d, y = %d \n", x, y);
   return 0;
}

