#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdatomic.h>
#define N 1000
#define M 5

void *f(void *args) {
    int *value = args;
    bool success;
    for (int i = 0; i < N; i++) {
        do {
            int r = *value;
            success = atomic_compare_exchange_weak(value, &r, r + 1);
        } while (!success);
    }
}

int main() {
    int value;
    pthread_t ids[M];
    for (int i = 0; i < M; i++)
        pthread_create(ids + i, NULL, &f, &value);
    for (int i = 0; i < M; i++)
        pthread_join(ids[i], NULL);
    printf("%d\n", value);
    return 0;
}
