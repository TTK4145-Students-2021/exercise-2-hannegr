// compile with:  gcc -g main.c ringbuf.c -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#include "ringbuf.h"

struct BoundedBuffer {
    struct RingBuffer*  buf;
    pthread_mutex_t     mtx;
    sem_t               empty;
    sem_t               full;
    
    
};

struct BoundedBuffer* buf_new(int size){
    struct BoundedBuffer* buf = malloc(sizeof(struct BoundedBuffer));
    buf->buf = rb_new(size);
    
    pthread_mutex_init(&buf->mtx, NULL);
    // TODO: initialize semaphores
    sem_init(&buf->full, 0, size); 
    // full: the semaphore-element given in bounded buffer, 0: any threads can use the semaphore, size: the initial value for the semaphore.
    sem_init(&buf->empty, 0, 0); 
    //empty: the semaphore-element given in bounded buffer, 0: any threads can use the semaphore,0 is the initial value for the semaphore. 
   



    //int    sem_init(sem_t *, int, unsigned int);
    //sem_init(&buf->full,  0, /*starting value?*/);
	//sem_init(&buf->empty, 0, /*starting value?*/);
    
    return buf;    
}

void buf_destroy(struct BoundedBuffer* buf){
    rb_destroy(buf->buf);
    pthread_mutex_destroy(&buf->mtx);
    sem_destroy(&buf->empty);
    sem_destroy(&buf->full);
    free(buf);
}




void buf_push(struct BoundedBuffer* buf, int val){   
    /*Hva tror jeg funksjonen min gjør? 
    - sjekker først om den har kapasitet til å legge til flere tall 
    - dekrementerer den fulle semaphoren når den har plass 
    - pusher den nye verdien når den kan det 
    - inkrementerer semaphoren når den er ferdig 
    - inkrementerer den tomme semaphoren, siden den nå bør ha plass til å kunne poppe (sier på en måte at det er nye elementer i bufferen med dette)

    */
    if(buf->buf->capacity != 0){
    sem_wait(&buf->full);
    rb_push(buf->buf, val); 
    sem_post(&buf->full); //unlocks the semaphore by incrementing it. 
    sem_post(&buf->empty); //increments the empty buffer, since it starts on 0, so it knows that it can be used. 
    }


}



    /*
    while(buf->buf->capacity == 0){
        //do nothing, just wait 
    }
    //waits for the capacity to be a positive number, so that it can add a number. 



    // TODO: make sure there is no concurrent access to the buffer internals
    sem_wait(&buf->full);
    //decrements the semaphore when it can be used

    rb_push(buf->buf, val);
    
    
    // TODO: signal that there are new elements in the buffer   
    sem_post(&buf->full); //unlocks the semaphore by incrementing it. 
    sem_post(&buf->empty); //increments the empty buffer, since it starts on 0, so it knows that it can be used. 
    */


int buf_pop(struct BoundedBuffer* buf){
    /* Hva tror jeg funksjonen min gjør? 
    - Sjekker om bufferen har elementer i seg 
    - dekrementerer den tomme semaphoren når den har plass 
    - inkrementerer den fulle semaphoren, siden den nå har plass til å legge til en ny
    - inkrementerer den tomme semaphoren, for å vise at den er ferdig. 
    */
    // TODO: same, but different?
    if(buf->buf->length != 0){
        sem_wait(&buf->empty);
    
        int val = rb_pop(buf->buf);  
        sem_trywait(&buf->empty);


        sem_post(&buf->empty); 
        return val; 
    }

}







    //unblocks the semaphore by incrementing it 

/*
    }
    while(buf->buf->length == 0){
        //do nothing, just wait 
    }
    //waits for the buffer to be filled with at least one element before it pops. 

    sem_wait(&buf->empty);
    //decrements the semaphore when it can be used
    
    int val = rb_pop(buf->buf);  


    sem_post(&buf->empty);  
    //unblocks the semaphore by incrementing it 
    
    return val;
    */






void* producer(void* args){
    struct BoundedBuffer* buf = (struct BoundedBuffer*)(args);
    
    for(int i = 0; i < 10; i++){
        nanosleep(&(struct timespec){0, 100*1000*1000}, NULL);
        printf("[producer]: pushing %d\n", i);
        buf_push(buf, i);
    }
    return NULL;
}

void* consumer(void* args){
    struct BoundedBuffer* buf = (struct BoundedBuffer*)(args);
    
    // give the producer a 1-second head start
    nanosleep(&(struct timespec){1, 0}, NULL);
    while(1){
        int val = buf_pop(buf);
        printf("[consumer]: %d\n", val);
        nanosleep(&(struct timespec){0, 50*1000*1000}, NULL);
    }
}

int main(){ 
    
    struct BoundedBuffer* buf = buf_new(5);
    
    pthread_t producer_thr;
    pthread_t consumer_thr;
    pthread_create(&producer_thr, NULL, producer, buf);
    pthread_create(&consumer_thr, NULL, consumer, buf);
    
    pthread_join(producer_thr, NULL);
    pthread_cancel(consumer_thr);
    
    buf_destroy(buf);
    
    return 0;
}
