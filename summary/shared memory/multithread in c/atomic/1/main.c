#include <stdio.h>
#include <stdbool.h>

int main() {
    int a = 2;
    bool b = __sync_bool_compare_and_swap(&a, 2, 3);
    printf("a: %d, b: %d\n", a, b);  // a: 3, b: 1
    return 0;
}
