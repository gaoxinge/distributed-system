#include <stdio.h>
#include <pthread.h>
#define N 1000
#define M 5

typedef struct {
    int value;
    pthread_mutex_t lock;
} Value;

void *f(void *args) {
    Value *value = args;
    for (int i = 0; i < N; i++) {
        pthread_mutex_lock(&value->lock);
        value->value++;
        pthread_mutex_unlock(&value->lock);
    }
}

int main() {
    Value value;
    value.value = 0;
    pthread_mutex_init(&value.lock, NULL);

    pthread_t ids[M];
    for (int i = 0; i < M; i++)
        pthread_create(&ids[i], NULL, &f, &value);
    for (int i = 0; i < M; i++)
        pthread_join(ids[i], NULL);
    printf("%d\n", value.value);
    return 0;
}
