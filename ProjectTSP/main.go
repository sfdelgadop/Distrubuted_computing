package main

import (
	"math/rand"
	"time"
)

func testfunc(genome []int) float32 {
	var rta float32 = 0.0
	for i, value := range genome {
		rta += float32(i * value)
	}
	return rta
}

func main() {
	size := 10
	rand.Seed(time.Now().UnixNano())

	agent1 := RandomAgent(size)
	agent1.Evaluate(testfunc)
	agent1.PrintAgent()

	Mutate(&agent1)
	agent1.Evaluate(testfunc)
	agent1.PrintAgent()

	agent2 := RandomAgent(size)
	agent2.Evaluate(testfunc)
	agent2.PrintAgent()

	agent3, agent4 := Crossover(&agent1, &agent2)
	agent3.Evaluate(testfunc)
	agent4.Evaluate(testfunc)

	agent3.PrintAgent()
	agent4.PrintAgent()
}
