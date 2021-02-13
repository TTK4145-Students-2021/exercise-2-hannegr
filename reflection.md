Problem 4 (I will use golang btw)

>I am almost 100% certain that I will use message passing, as I see many possibilities. For instance each elevator can have one receiving channel and one sending channel. We can 
also have kind of a main system master that has a receiving, and a sending channel.  The elevator then can send a message about which floor the elevator is in, if it is idle, 
going up ect. (so yeah, I will probably also make an fsm for this). Then the master can send a request to the nearest available elevator, and the elevator can send 
a signal to the master receiving channel when it accepts the request, when it takes on the passenger and when it arrives at the correct destination. In that way we also know that it
is done, because if not a timer could be used to see that something went wrong for instance. Global variables are also generally more unsafe, as they can be changed when they are 
not supposed to. Concurrency may also be a good idea, as several elevators will be able to do stuff at the same time. 

> I might split the system into goroutines, lightweigt threads that will communicate via channels, and the reason is mentioned above. It can also be smart to use a struct to make 
the states in the fsm. A big focus should probably be on error, and it could be a good idea to make a class that handles errors, for instance returns the system into a safe state if 
the stud.ass turns off the electricity. 

> For the networking part, Go has a standard library called "net" which makes TCP and UDP work. Another called gnet (https://github.com/panjf2000/gnet) also has a SO_REUSEPORT socket
option, so that Listening sockets in UDP or TCP can listen on the same channel.


> Go has a data race detector that can handle data races and race conditions. This website, https://golang.org/doc/articles/race_detector.html#How_To_Use, provides info about how to 
use it, and it seems like it can be used for many different types of errors we might have (global variables and sending messages for instance). To just print an error-message if 
something goes wrong is also an option, even though it is not very cool, and it assumes that we know what could go wrong. Go has a library, testing, that runs unit tests and can 
send an error message if there is an error, and a fatal message if the error is so bad that the system must be stopped. For messages one can also use something calles "heartbeat", 
kind of like a watchdog, a periodic signal that can be sent to say that everything is going well. For instance, you can give the elevator packages in a specified interval, and if 
they don't get it, they system will complain that something is wrong. Then something is probably wrong with the master, and the slave must take over. 

> The IDE I use now is Goland, but Visual Studio also works as an IDE for go. Both have analysis of the sourcecode, as well as debuggingsupport, so I think that covers all I need. 


