#include <stdio.h>

int main() {
#ifdef DEBUG
    printf("Debug hello, world.\n");
#else
    printf("Release hello, world.\n");
#endif
    return 0;
}
