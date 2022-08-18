package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"time"
)

func main() {
	fmt.Println("Algoritmo Quicksort")

	tamanios := [29]int{100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
		10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000,
		90000, 100000, 110000, 120000, 130000, 140000, 150000,
		200000, 300000, 400000, 500000}
	pruebas := 11

	for k := 0; k < len(tamanios); k++ {
		for l := 1; l < pruebas; l++ {
			var datos int
			tamanio := tamanios[k]
			lista := []int{}

			archivo, err := os.Open("1000000_random_numbers.txt")
			if err != nil {
				log.Fatal(err)
			}

			archivoDatos := bufio.NewScanner(archivo)

			for archivoDatos.Scan() {

				datos, err = strconv.Atoi(archivoDatos.Text())
				lista = append(lista, datos)

			}
			tiempoInicio := time.Now()
			quicksort(lista, 0, tamanio-1)
			tiempoFinal := time.Since(tiempoInicio)

			fmt.Print(strconv.Itoa(l) + ";" + strconv.Itoa(tamanio) + ";")
			fmt.Println(tiempoFinal.Milliseconds())
			defer archivo.Close()
		}
	}
}

func quicksort(lista []int, primero int, ultimo int) {

	central := (primero + ultimo) / 2
	pivote := lista[central]
	i := primero
	j := ultimo

	for i <= j {
		for lista[i] < pivote {
			i += 1
		}
		for lista[j] > pivote {
			j -= 1
		}
		if i <= j {
			tmp := lista[i]
			lista[i] = lista[j]
			lista[j] = tmp
			i += 1
			j -= 1
		}
	}
	if primero < j {
		quicksort(lista, primero, j)
	}
	if i < ultimo {
		quicksort(lista, i, ultimo)
	}

}
