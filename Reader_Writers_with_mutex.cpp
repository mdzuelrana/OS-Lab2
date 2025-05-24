#include <iostream>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t resource = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t readCountMutex = PTHREAD_MUTEX_INITIALIZER;

int readCount = 0;

void* reader(void* arg) {
    int id = *((int*)arg);
    pthread_mutex_lock(&readCountMutex);
    readCount++;
    if (readCount == 1)
        pthread_mutex_lock(&resource);
    pthread_mutex_unlock(&readCountMutex);

    std::cout << "Reader " << id << " is reading.\n";
    sleep(1);

    pthread_mutex_lock(&readCountMutex);
    readCount--;
    if (readCount == 0)
        pthread_mutex_unlock(&resource);
    pthread_mutex_unlock(&readCountMutex);
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    pthread_mutex_lock(&resource);

    std::cout << "Writer " << id << " is writing.\n";
    sleep(2);

    pthread_mutex_unlock(&resource);
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int ids[] = {1, 2, 3, 4, 5};

    pthread_create(&r[0], NULL, reader, &ids[0]);
    pthread_create(&w[0], NULL, writer, &ids[3]);
    pthread_create(&r[1], NULL, reader, &ids[1]);
    pthread_create(&r[2], NULL, reader, &ids[2]);
    pthread_create(&w[1], NULL, writer, &ids[4]);

    for (int i = 0; i < 3; ++i) pthread_join(r[i], NULL);
    for (int i = 0; i < 2; ++i) pthread_join(w[i], NULL);

    return 0;
}
