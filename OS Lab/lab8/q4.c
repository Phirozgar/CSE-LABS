#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 3

sem_t waitingRoom, barberChair, barberSleep, seatBelt;

void *barber(void *arg) {
    while (1) {
        sem_wait(&barberSleep); // Barber sleeps until a customer arrives
        sem_wait(&barberChair); // Barber chair is free
        printf("Barber is cutting hair...\n");
        sleep(2);
        printf("Barber finished cutting hair.\n");
        sem_post(&barberChair);
        sem_post(&seatBelt);   // Customer leaves
    }
}

void *customer(void *arg) {
    int id = *((int *)arg);

    if (sem_trywait(&waitingRoom) == 0) {
        printf("Customer %d entered waiting room.\n", id);

        sem_wait(&barberChair);
        sem_post(&waitingRoom);

        printf("Customer %d waking up barber.\n", id);
        sem_post(&barberSleep);

        sem_post(&barberChair); // sit on chair
        sem_wait(&seatBelt);    // wait till haircut done
        printf("Customer %d leaving after haircut.\n", id);
    } else {
        printf("Customer %d left (no chairs available).\n", id);
    }
    return NULL;
}

int main() {
    pthread_t b, c[10];
    int ids[10];

    sem_init(&waitingRoom, 0, CHAIRS);
    sem_init(&barberChair, 0, 1);
    sem_init(&barberSleep, 0, 0);
    sem_init(&seatBelt, 0, 0);

    pthread_create(&b, NULL, barber, NULL);

    for (int i=0; i<10; i++) {
        ids[i] = i+1;
        sleep(1);
        pthread_create(&c[i], NULL, customer, &ids[i]);
    }

    for (int i=0; i<10; i++)
        pthread_join(c[i], NULL);

    return 0;
}

