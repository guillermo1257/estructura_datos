// Counting Sort solo para enteros positivos
package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
	"time"
)

func countSort(arr []int) []int {
	var max = arr[0]

	var i = 1
	for i < len(arr) {
		if arr[i] > max {
			max = arr[i]
		}
		i++
	}

	var indices = make([]int, max+1)

	var j = 0
	for j < len(arr) {
		indices[arr[j]]++
		j++
	}

	var k = 1
	for k < len(indices) {
		indices[k] += indices[k-1]
		k++
	}

	var result = make([]int, len(arr))

	var m = 0
	for m < len(arr) {
		result[indices[arr[m]]-1] = arr[m]
		indices[arr[m]]--
		m++
	}
	return result
}

func printArray(arr []int) {
	fmt.Print(strings.Trim(fmt.Sprint(arr), "[]"))
}

func main() {
	fmt.Println("Algoritmo MergeSort")

	tamanios := [29]int{100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
		10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000,
		90000, 100000, 110000, 120000, 130000, 140000, 150000,
		200000, 300000, 400000, 500000}
	//tamanios := [1]int{10}
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
			sorted := countSort(listacorta)
			fmt.Println(sorted) //habilitar si imprimir array ordenados
			tiempoFinal := time.Since(tiempoInicio)

			fmt.Print(strconv.Itoa(l) + ";" + strconv.Itoa(tamanio) + ";")
			fmt.Println(tiempoFinal.Milliseconds())
			defer archivo.Close()
		}
	}
}
