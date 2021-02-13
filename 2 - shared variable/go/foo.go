// Use `go run foo.go` to run your program

package main

import (
	"fmt"
	"runtime"
)

func number_server(add <-chan int, sub <-chan int, read chan<- int) {
	var number = 0

	for {
		select {
		case num := <-add: //received num from add
			number += num

		case num2 := <-sub: //received num2 from sub
			number -= num2

		case read <- number: //0 sent to channel read
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
	}
	//TODO: signal that the goroutine is finished
	finished <- true
}

func decrementer(sub chan<- int, finished chan<- bool) {
	for j := 0; j < 1000000; j++ {
		sub <- 1
	}
	//TODO: signal that the goroutine is finished
	finished <- true
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

	//this means that the receiving from ch4 and ch3 is blocked forever
	<-ch4
	<-ch3

	fmt.Println("The magic number is:", <-read)
}
