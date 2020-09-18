package main

import (
	"fmt"
	"time"
)

/*-- POSIX/pi --*/

//ITERATIONS to calculate pi
var ITERATIONS int = 1.0e+9

//THREADS to compare
var THREADS int = 16

func pi(id int, ch chan float64) {
	bash := ITERATIONS / THREADS
	init := id * bash
	end := init + bash

	pi := 0.0

	for {
		pi += 4.0 / float64((2*init)+1)
		init++
		pi -= 4.0 / float64((2*init)+1)
		init++

		if init == end {
			break
		}
	}

	ch <- pi
}

func main() {
	start := time.Now()

	ch := make(chan float64, THREADS)

	for i := 0; i < THREADS; i++ {
		go pi(i, ch)
	}

	piTotal := 0.0

	for i := 0; i < THREADS; i++ {
		piTotal += <-ch
	}

	elapsed := time.Since(start)
	fmt.Printf("Pi: %0.20f\n", piTotal)
	fmt.Printf("Time: %f\n", elapsed.Seconds())
}
