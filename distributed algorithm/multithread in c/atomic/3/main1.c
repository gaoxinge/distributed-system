#include <stdio.h>
#include <stdbool.h>
#include <stdatomic.h>

int main() {
    int a = 2;
    int expected = 3;
    int desired = 3;
    bool b = atomic_compare_exchange_weak(&a, &expected, desired);
    printf("a: %d, b: %d\n", a, b);  // a: 2, b: 0
    return 0;
}
