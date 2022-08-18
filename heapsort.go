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
	fmt.Println("Algoritmo Heapsort")

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

			listacorta := []int{}
			for p := 0; p < tamanio; p++ {
				listacorta = append(listacorta, lista[p])
			}

			tiempoInicio := time.Now()
			heapSort(listacorta)

			tiempoFinal := time.Since(tiempoInicio)

			fmt.Print(strconv.Itoa(l) + ";" + strconv.Itoa(tamanio) + ";")
			fmt.Println(tiempoFinal.Milliseconds())
			defer archivo.Close()
		}
	}
}

func heapify(arr []int, n int, i int) {
	var largest = i
	var l = 2*i + 1
	var r = 2*i + 2

	if l < n && arr[i] < arr[l] {
		largest = l
	}

	if r < n && arr[largest] < arr[r] {
		largest = r
	}

	if largest != i {
		arr[i], arr[largest] = arr[largest], arr[i]
		heapify(arr, n, largest)
	}
}

func heapSort(arr []int) {
	n := len(arr)

	for i := n / 2; i > -1; i-- {
		heapify(arr, n, i)
	}

	for i := n - 1; i > -1; i-- {
		arr[i], arr[0] = arr[0], arr[i]
		heapify(arr, i, 0)
	}
}
