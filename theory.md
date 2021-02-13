Exercise 2 - Theory questions
-----------------------------

### What is an atomic operation?
> An atomic operation is often used in concurrent programming, and is an operation that runs independently of the other operations in a program. An atomic action does not reveal its state until it is done doing the action. Atomic operations can be needed to avoid data races, and they are for instance much used for read and write. 

### What is a critical section?
> A critical section is a section of the code that makes sure that a shared variable is only used by one process at a time. The C-code in task 2 has a critical section for instance, due to the use of mutex to lock and unlock the global variable i (and in that way protecting it).

### What is the difference between race conditions and data races?
> I have written that atomic operations can be needed to avoid data races. This is because a data race occurs when more threads try to access the same memory location. If one of these threads is a write, it can cause problems because if it writes before another thread can for instance read, it can cause another output for the read-thread than expected. Race conditions, on the other hand, occur more in critical sections. This is basically if two or more tasks in a critical section are performed/executed in the wrong order. 

### What are the differences between semaphores, binary semaphores, and mutexes?
> The little book of semaphores has a really good definition of a semophore. It is basically a signaling-mechanism that can be used if a lot of processes needs to access something, to say whether it is ready to be accessed or not. Its value at first can be initialized to any integer (over 0), and afterwards it can be incremented or decremented by threads. If a thread then decrements the semaphore and it gives out a negative result, the thread will be blocked and not unblocked until another thread increments the semaphore. A binary semaphore is like a semaphore, but can only have binary values (0 and 1). It is initialized to 1 so that a thread that needs the resource this semaphore can give access to will get it, and can decrement it to 0. This means that only one thread can do something with the resource at the time. A Mutex works like a binary semaphore, but it is not a semaphore. Mutex means Mutual Exlusion object, and like the name states it also tells whether a resource can be accessed at the time or not. But it is more similar to a lock, and its two operations are either lock, where a thread has locked it and only that thread can open it, or unlock, where no threads have locked it yet. 


### What are the differences between channels (in Communicating Sequential Processes, or as used by Go, Rust), mailboxes (in the Actor model, or as used by Erlang, D, Akka), and queues (as used by Python)? 
> A channel is something that makes room for message-passing between threads. A message is sent over a channel, where one or more threads are the transimitters and one or more threads are the receivers. A mailbox is basically like its name, a mailbox. It is used to pass messages between threads, and one thread can read to it and another can write to it. A queue is like a mailbox, and passes communication around. The difference is that it is just a datatype, while a mailbox is a message-passing type. A mailbox is also FIFO, and a queue don't necessarily have to be that. 

### List some advantages of using message passing over lock-based synchronization primitives.
> A message-passing system shares data by sending and receiving messages, while a lock-based system communicate using shared variables. These global variables can be modified without someone meaning to, which can cause weird behaviour. That will not happen with message-passing. Also, deadlock can occur in lock-based systems if two or more processes are waiting for each other. 

### List some advantages of using lock-based synchronization primitives over message passing
> In message-passing there are more processes going on at once. A message needs a sender and a receiver, and the sender and receiver need to do the processes involved in sending a message. This can be harder to implement in the code. In problem 2, the go-code for instance requires more code than the C-code, and it still leads to the same thing. Another advantage of lock-based is that it is often faster than message passing. 