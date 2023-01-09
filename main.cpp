#include <bits/stdc++.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define SIZE 10
typedef int buffer_item;

buffer_item BUFFER[SIZE];
int in = 0, out = 0;
int items = 0;

// Semaphores and Mutex Lock
sem_t Full, Empty;
pthread_mutex_t Mutex;


// Print items in buffer
void printBuffer(){
    std::cout<<"\n\nBUFFER: [ ";
    for(int i = 0; i < SIZE; i++){
        std::cout<<BUFFER[i]<<" ";
    }
    std::cout<<"]\n\n";
}

// insert item in buffer
int insertItem(buffer_item item){
    int flag;
    if(items != SIZE && BUFFER[in] == 0){
        BUFFER[in] = item;
        in = (in + 1) % SIZE;
        items++;

        std::cout<<"Item Produced: "<<item;
        printBuffer();

        flag = 1;
    }
    else
        flag = 0;

    return flag;
}

// remove item from buffer
int removeItem(){
    buffer_item item;
    int flag;

    if(items != 0 && BUFFER[out] != 0){
        item = BUFFER[out];
        BUFFER[out] = 0;

        out = (out + 1) % SIZE;
        items--;

        std::cout<<"Item Removed: "<<item;
        printBuffer();

        flag = 1;
    }
    else
        flag = 0;

    return flag;
}

void *myProducer(void *param){
    
    buffer_item item;
    while(true){
        sleep(rand() % 5 + 1);

        // wait for buffer to get empty, if so, lock the current producer
        sem_wait(&Empty);
        pthread_mutex_lock(&Mutex);

        // start critical section
        std::cout<<"Entered crticial section of Producer!"<<std::endl;

        item = (rand() % 20) + 1;
        if(!insertItem(item))
            std::cout<<"Failed to insert element. Buffer is full!!!";

        // end of critical section

        // unlock the producer, signal full semaphore
        pthread_mutex_unlock(&Mutex);
        sem_post(&Full);
    }
}

void *myConsumer(void *param){

    while(true){
        sleep(rand() % 5 + 1);

        // wait for buffer to get full. If so, lock the current consumer
        sem_wait(&Full);
        pthread_mutex_lock(&Mutex);

        // start of critical section
        std::cout<<"Entered crtical section of Consumer!"<<std::endl;

        if(!removeItem())
            std::cout<<"Failed to remove item from buffer!!!";
        
        // end of critical section

        // unlock the consumer, signal empty semaphore
        pthread_mutex_unlock(&Mutex);
        sem_post(&Empty);
    }
}


int main(int argc, char *argv[]){

    int prds, cons, runTime;

    if(argc != 4){
        std::cout<<"Missing args!!!"<<std::endl;
        exit(1);
    } else {
        prds = atoi(argv[1]);
        cons = atoi(argv[2]);
        runTime = atoi(argv[3]);
    }

    pthread_mutex_init(&Mutex, NULL);
    sem_init(&Empty, 0, SIZE);
    sem_init(&Full, 0, 0);

    pthread_t Producers[prds], Consumers[cons];

    for(int i = 0; i <  prds; i++)
        pthread_create(&Producers[i], NULL, myProducer, NULL);
    for(int i = 0; i <  cons; i++)
        pthread_create(&Consumers[i], NULL, myConsumer, NULL);

    sleep(runTime);

    std::cout<<"\nExiting..."<<std::endl;

    for(int i = 0; i < prds; i++)
        pthread_cancel(Producers[i]);
    for(int i = 0; i < cons; i++)
        pthread_cancel(Consumers[i]);

    pthread_mutex_destroy(&Mutex);
    sem_destroy(&Empty);
    sem_destroy(&Full);

    return 0;
}