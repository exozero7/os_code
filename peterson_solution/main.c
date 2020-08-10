#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

pthread_t tid[2];
int turn = 0;
bool flag[2] = {false, false};

int thread0_turn = 0;
int thread1_turn = 1;

int steps = 0;

FILE* f;

void* entry_point_function(void* arg){

    int thread = *((int*)arg);
    int other_thread = (thread + 1) % 2;
    
    while (steps < 10){
        flag[thread] = true;
        /* Give turn to the other thread */
        turn = other_thread;
        printf("Thread %d waiting\n", thread);
        /* Wait */
        while(flag[other_thread] && turn == other_thread);

        /* Critical Section */
        f = fopen("share.txt", "a");
        fprintf(f, "I'm thread %d\n", thread);
        
        flag[thread] = false;

        steps++;
    }
}

int main(void){

    pthread_create(&tid[0], NULL, entry_point_function, (void*)&thread0_turn);
    pthread_create(&tid[1], NULL, entry_point_function, (void*)&thread1_turn);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}