#include <stdio.h>
#include <stdbool.h>

int main() {
    int a = 2;
    int expected = 2;
    int desired = 3;
    bool b = __atomic_compare_exchange(&a, &expected, &desired, true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    printf("a: %d, b: %d\n", a, b);  // a: 3, b: 1
    return 0;
}
