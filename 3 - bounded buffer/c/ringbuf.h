#pragma once

struct RingBuffer {
    int* buffer;
    int capacity;
    
    int insertIdx;
    int removeIdx;
    int length;
};
//struct with int-poninter buffer, an int that shows the capacity, an int for insertindex, and int to remove an index and an int that shows the length


struct  RingBuffer* rb_new(int size); 
/*making a ringbuffer-object called rb_new, with a specified size, int-size. The size of buffer is then malloced, the capacity is size and the rest of the ints in the struct are set to 0. 
*/
void    rb_destroy(struct RingBuffer* rb); 
/*frees the ringbuffer 
*/

void    rb_push(struct RingBuffer* rb, int val);//put data into the buffer
/*checks if the buffer is not full, then puts data (int val) into the buffer in the place insertIdx. Adds 1 to the length, and changes place of insertidx. 
*/
int     rb_pop(struct RingBuffer* rb);
/*Checks if the buffer is empty, if not it removes an element, removes 1 from the length and changes place of removeidx. 
*/

void    rb_print(const struct RingBuffer* const rb);
/*prints the elements of the ringbuffer*/


