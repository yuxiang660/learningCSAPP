#include <stdio.h>
#include <stdlib.h>

#ifdef COMPILETIME
#define malloc(size) mymalloc(size)
#define free(ptr) myfree(ptr)

void* mymalloc(size_t size);
void myfree(void* ptr);
#endif

int main()
{
   int* p = malloc(32);
   printf("main | malloc return %p\n", p);
   free(p);
   return 0;
}
