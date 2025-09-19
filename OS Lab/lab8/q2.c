#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int readcount = 0, data = 0;

void *reader(void *arg) {
    int id = *((int *)arg);

    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);

    printf("Reader %d reads data = %d\n", id, data);
    sleep(1);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    sem_post(&mutex);
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);

    sem_wait(&wrt);
    data++;
    printf("Writer %d writes data = %d\n", id, data);
    sem_post(&wrt);
    return NULL;
}

int main() {
    pthread_t r[5], w[3];
    int ids[5] = {1,2,3,4,5};

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i=0; i<3; i++)
        pthread_create(&w[i], NULL, writer, &ids[i]);

    for (int i=0; i<5; i++)
        pthread_create(&r[i], NULL, reader, &ids[i]);

    for (int i=0; i<3; i++)
        pthread_join(w[i], NULL);
    for (int i=0; i<5; i++)
        pthread_join(r[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}

