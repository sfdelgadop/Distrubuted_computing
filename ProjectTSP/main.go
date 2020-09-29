package main

import (
	"fmt"
	"math/rand"
	"time"
)

const indSize = 10
const popSize = 20
const generations = 50

func testfunc(genome []int) float32 {
	var rta float32 = 0.0
	for i, value := range genome {
		rta += float32(i * value)
	}
	return rta
}

func initPopulation(function func([]int) float32) [popSize]Agent {
	var population [popSize]Agent
	for i := range population {
		population[i] = RandomAgent(indSize)
		population[i].Evaluate(function)
	}
	return population
}

func getBest(agents ...Agent) Agent {
	best := agents[0]
	for _, agent := range agents {
		if agent.fitness > best.fitness {
			best = agent
		}
	}
	return best
}

func main() {
	rand.Seed(time.Now().UnixNano())
	population := initPopulation(testfunc)

	i := 0
	var offspring [popSize]Agent
	for i < generations {
		fmt.Printf("Best %d: ", i)
		getBest(population[:]...).PrintAgent()
		for j := range population {
			if rand.Float32() < 1 {
				pair := rand.Intn(popSize)
				n1, n2 := Crossover(&population[j], &population[pair])
				n1.Evaluate(testfunc)
				n2.Evaluate(testfunc)
				best := getBest(n1, n2)
				Mutate(&best)
				best.Evaluate(testfunc)
				offspring[j] = getBest(population[j], best)
			} else {
				offspring[j] = population[j]
			}
		}
		population = offspring
		i++
	}
	fmt.Printf("Best %d: ", i)
	getBest(population[:]...).PrintAgent()
}
