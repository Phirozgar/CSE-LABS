#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 20

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int produced = 0, consumed = 0;

sem_t empty, full, mutex;

void *producer(void *arg) {
    for (int i = 0; i < 10; i++) {  
        // Wait until producer is not ahead of consumer by more than 10
        while ((produced - consumed) >= 10) {
            usleep(100000);
        }

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = i + 1;
        printf("Producer produced item %d\n", buffer[in]);
        in = (in + 1) % BUFFER_SIZE;
        produced++;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        consumed++;

        sem_post(&mutex);
        sem_post(&empty);

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}

