#include <stdio.h>
#include <pthread.h>

void *f(void *args) {
    printf("fuck");
}

int main() {
    pthread_t id;
    pthread_create(&id, NULL, &f, NULL);
    pthread_join(id, NULL);
    return 0;
}