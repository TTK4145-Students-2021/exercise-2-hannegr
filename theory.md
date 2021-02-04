Exercise 2 - Theory questions
-----------------------------

### What is an atomic operation?
> An atomic operation is often used in concurrent programming, and is an operation that runs independently of the other operations in a program. Atomic operations can be needed to avoid data races, and they are for instance much used for read and write. 

### What is a critical section?
> A critical section is a sequence of task for which it is critical that they execute in some given order. This is made possible by atomic actions.

### What is the difference between race conditions and data races?
> I have written that atomic operations can be needed to avoid data races. This is because a data race occurs when more threads access the same memory location. If one of these threads is a write, it can cause problems because if it writes before another thread can for instance read, it can cause another output for the read-thread than expected. Race conditions, on the other hand, occur more in criticaol sections. This is basically if two or more tasks in a critical section are preformed/executed in the wrong order. 

### What are the differences between semaphores, binary semaphores, and mutexes?
> The little book of semaphores has a really good definition of a semophore. It is basically a data type that can be used if a lot of processes needs to access something, to say whether it is ready to be accessed or not. Its value at first can be initialized to any integer (over 0), and afterwards it can be incremented or decremented by threads. If a thread then decrements the semaphore and it gives out a negative result, the thread will be blocked and not unblocked until another thread increments the semaphore. Since the value of the semaphore cannot be read, it is nearly impossible to know if a thread decrementing the semaphore will be blocked or not. A binary semaphore is like a semaphore, but can only have binary values (0 and 1). It is initialized to 1 so that a threads that needs the resource this semaphore can give access to, it will get it and can decrement to 0. This means that only one thread can do something with the resource at the time. A Mutex works like a binary semaphore, but it is not a semaphore. Mutex means Mutual Exlusion object, and like the name states it also tells whether a resource can be accessed at the time or not. But it is more similar to a lock, and its two operations are either lock, where a thread has locked it and only that thread can open it, or unlock, where no threads have locked it yet. 

### What are the differences between channels (in Communicating Sequential Processes, or as used by Go, Rust), mailboxes (in the Actor model, or as used by Erlang, D, Akka), and queues (as used by Python)? 
> A channel is something that make room for message-passing between threads. A message is sent over a channel, where one or more threads are the transimitters and one or more threads are the receivers. A mailbox is basically like its name, a mailbox. It is used to pass messages between threads, and one thread can read to it and another can write to it. A queue is like a mailbox, and passes communication around. Since queue instances in Python have locking mechanisms (https://www.geeksforgeeks.org/python-communicating-between-threads-set-1/), it can be shared by many threads without something bad happening. 

### List some advantages of using message passing over lock-based synchronization primitives.
> In a message passing system the reciever of the message(s) will be notified if someone sends a message. This won't happen with lock-based, as ........something? Message passing can also happen asynchronously. 

### List some advantages of using lock-based synchronization primitives over message passing.
> asynronous message passing can lead to deadlock. 