#include <stdio.h>
#include <pthread.h>
#define N 1000
#define M 5

void *f(void *args) {
    int *value = args;
    for (int i = 0; i < N; i++)
        *value++;
}

int main() {
    int value = 0;
    pthread_t ids[M];
    for (int i = 0; i < M; i++)
        pthread_create(&ids[i], NULL, &f, &value);
    for (int i = 0; i < M; i++)
        pthread_join(ids[i], NULL);
    printf("%d\n", value);
    return 0;
}
