// Use `go run foo.go` to run your program
//THESE COMMENTS ARE FOR ME
//goroutine: lightweight thread managed by go runtime If you make a function and run go that function and another function,
//both will run at the same time.
//channel: send and receive values. Data flows in the direction of the values. ch <- v: v is sent to channel ch. v:= <- ch: recieve from ch and
//assign value to v.
//create channel by: ch := make(chan int)
//Channels can be buffered using ch := make(chan int, number), will then block when number of messages is bigger than number.
//close(ch): close channel
//select: blocks until one of its cases can run, then run that case. Chooses a random if multiple are ready.
//select{
//		*do stuff
//      }

package main

import (
	"fmt"
	"runtime"
)

func number_server(add <-chan int, sub <-chan int, read chan<- int) {
	var number = 0

	// This for-select pattern is one you will become familiar with...
	for {
		select {
		case num := <-add:
			number += num

		case num2 := <-sub:
			number -= num2

		case read <- number:
			return

		}

	}
}

//Using shared variable synchronization is possible, but not the idiomatic approach in Go.
//You should instead create a server that is responsible for its own data, select{}s messages, and perform different actions on its data when it receives a corresponding message.
//The server should have three actions it can perform: Increment, decrement, and read (or "get"). Two other goroutines should send the increment and decrement requests to the server,
//and main should read out the final value after these two goroutines are done.

func incrementer(add chan<- int, finished chan<- bool) {
	for j := 0; j < 1000000; j++ {
		add <- 1
		finished <- true
	}
	//close(finished)
	//defer close(add)
	//TODO: signal that the goroutine is finished¨
	//if(finished == true):

}

func decrementer(sub chan<- int, finished chan<- bool) {
	for j := 0; j < 1000000+1; j++ {
		sub <- 1
		finished <- true
	}
	//defer close(sub)
	//TODO: signal that the goroutine is finished
	//if(finished == true):
	//	close(finished)

}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())
	// TODO: Construct the remaining channels
	ch1 := make(chan int)
	ch2 := make(chan int)
	ch3 := make(chan bool)
	ch4 := make(chan bool)

	// TODO: Spawn the required goroutines
	read := make(chan int)
	go number_server(ch1, ch2, read)
	go incrementer(ch1, ch3)
	go decrementer(ch2, ch4)

	// TODO: block on finished from both "worker" goroutines
	<-ch4
	<-ch3

	//close(ch4)
	//close(ch1)
	//close(ch2)

	fmt.Println("The magic number is:", <-read)
}
