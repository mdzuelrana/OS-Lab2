#include <iostream>
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

std::queue<int> buffer;
pthread_mutex_t mutex;
sem_t emptySlots, fullSlots;

void* producer(void*) {
    for (int i = 0; i < 10; ++i) {
        sem_wait(&emptySlots);
        pthread_mutex_lock(&mutex);

        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;

        pthread_mutex_unlock(&mutex);
        sem_post(&fullSlots);
        sleep(1);
    }
    return NULL;
}

void* consumer(void*) {
    for (int i = 0; i < 10; ++i) {
        sem_wait(&fullSlots);
        pthread_mutex_lock(&mutex);

        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << item << std::endl;

        pthread_mutex_unlock(&mutex);
        sem_post(&emptySlots);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&emptySlots, 0, SIZE);
    sem_init(&fullSlots, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
