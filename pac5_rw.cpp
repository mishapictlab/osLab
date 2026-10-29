
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

int data = 0, count = 0;
sem_t wrt;
pthread_mutex_t mutex;

void* reader(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mutex);
    count++;
    if (count == 1) sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);

    cout << "Reader " << id << " reads: " << data << endl;

    pthread_mutex_lock(&mutex);
    count--;
    if (count == 0) sem_post(&wrt);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;

    sem_wait(&wrt);

    data += 10;
    cout << "Writer " << id << " writes: " << data << endl;

    sem_post(&wrt);
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int rid[3] = {1, 2, 3}, wid[2] = {1, 2};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &rid[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &wid[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}