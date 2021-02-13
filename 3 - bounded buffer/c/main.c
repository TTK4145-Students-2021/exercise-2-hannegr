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
    /*Hva gjør funksjonen min?
    - sjekker først om den har kapasitet til å legge til flere tall 
    - dekrementerer den fulle semaphoren når den har plass 
    - får tak i nøkkelen mtx, for å si at den tråden skal jobbe nå
    - pusher verdien inn 
    - låser opp, da den er ferdig
    - inkrementerer den 
    - inkrementerer semaphoren når den er ferdig 
    - inkrementerer semaphore empty for å si at nå er det et til element i bufferen som kan poppes 

    */
    if(buf->buf->capacity != 0){
        sem_wait(&buf->full);
        pthread_mutex_lock(&buf->mtx);
        rb_push(buf->buf, val); 
        pthread_mutex_unlock(&buf->mtx);
        sem_post(&buf->empty); 
    }


}



int buf_pop(struct BoundedBuffer* buf){
    /* Hva gjør funksjonen min? 
    - Sjekker om bufferen har elementer i seg, ved å finne lengden
    - dekrementerer dem tomme semaphoren når den har plass
    - Får tak i nøkkelen mtx, for å si at det er den tråden som popper som trenger å jobbe nå 
    - fjerner verdien fra bufferen 
    - låser opp mutexen igjen slik at andre tråder kan kjøre 
    - inkrementerer semaphore full, for å si at det nå er en til plass i bufferen
    */
    // TODO: same, but different?
    if(buf->buf->length != 0){
        sem_wait(&buf->empty);
        pthread_mutex_lock(&buf->mtx); 
        int val = rb_pop(buf->buf);  
        pthread_mutex_unlock(&buf->mtx); 
        sem_post(&buf->full); 
        
        return val; 
    }

}

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
    
    pthread_create(&consumer_thr, NULL, consumer, buf);
    pthread_create(&producer_thr, NULL, producer, buf);

 
    pthread_join(producer_thr, NULL);
    pthread_cancel(consumer_thr);
    

    
    buf_destroy(buf);
    
    return 0;
}
