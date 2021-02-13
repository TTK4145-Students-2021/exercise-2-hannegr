package main

import (
	"fmt"
	"time"
)

func producer(input chan<- int) {

	for i := 0; i < 10; i++ {
		time.Sleep(100 * time.Millisecond)
		fmt.Printf("[producer]: pushing %d\n", i)
		// TODO: push real value to buffer
		input <- i //send i to input
	}

}

func consumer(output chan int) {

	time.Sleep(1 * time.Second)
	for {
		i := <-output //TODO: get real value from buffer
		//receive from output
		fmt.Printf("[consumer]: %d\n", i)
		time.Sleep(50 * time.Millisecond)
	}

}

func main() {

	// TODO: make a bounded buffer
	bounded_buffer := make(chan int, 5) //make Channel: need a channel with a buffer capacity 5.

	go consumer(bounded_buffer)
	go producer(bounded_buffer)

	select {}
}
