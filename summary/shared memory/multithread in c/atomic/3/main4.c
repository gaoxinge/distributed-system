#include <stdio.h>
#include <pthread.h>
#define N 1000
#define M 5

_Atomic int value;

void *f(void *args) {
    for (int i = 0; i < N; i++)
        value++;
}

int main() {
    pthread_t ids[M];
    for (int i = 0; i < M; i++)
        pthread_create(ids + i, NULL, &f, NULL);
    for (int i = 0; i < M; i++)
        pthread_join(ids[i], NULL);
    printf("%d\n", value);
    return 0;
}
