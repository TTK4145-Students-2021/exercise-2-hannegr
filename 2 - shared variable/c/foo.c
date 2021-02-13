#include <pthread.h>
#include <stdio.h>
//mutexe or semaphores? - Here I choose mutex, because we only have two threads anyways, so it will work out allright to lock and unlock. I could also have used a binary semaphore. 

int i = 0;
pthread_mutex_t mutex; 

// Note the return type: void*
void* incrementingThreadFunction(){
    for (int j = 0; j < 1000000; j++) {
	//synched access to i 
    pthread_mutex_lock(&mutex);
    i++;
    pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* decrementingThreadFunction(){
    for (int j = 0; j < 1000000; j++) {
    //synched access to i 
    pthread_mutex_lock(&mutex);
    i--;
    pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(){
    pthread_t incrementingThread, decrementingThread;
    
    pthread_create(&incrementingThread, NULL, incrementingThreadFunction, NULL);
    pthread_create(&decrementingThread, NULL, decrementingThreadFunction, NULL);
    
    pthread_join(incrementingThread, NULL);
    pthread_join(decrementingThread, NULL);
    
    printf("The magic number is: %d\n", i);
    return 0;
}
