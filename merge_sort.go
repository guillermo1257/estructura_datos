package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"time"
)

func mergeSort(array []int) []int {
	if len(array) < 2 {
		return array
	}
	medio := len(array) / 2
	izquierda := mergeSort(array[:medio])
	derecha := mergeSort(array[medio:])
	return merge(izquierda, derecha)
}

func merge(a []int, b []int) []int {
	final := []int{}
	i := 0
	j := 0

	for i < len(a) && j < len(b) {
		if a[i] < b[j] {
			final = append(final, a[i])
			i++
		} else {
			final = append(final, b[j])
			j++
		}
	}
	for ; i < len(a); i++ {
		final = append(final, a[i])
	}
	for ; j < len(b); j++ {
		final = append(final, b[j])
	}
	return final
}

func main() {
	fmt.Println("Algoritmo MergeSort")

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
			mergeSort(listacorta)
			tiempoFinal := time.Since(tiempoInicio)

			fmt.Print(strconv.Itoa(l) + ";" + strconv.Itoa(tamanio) + ";")
			fmt.Println(tiempoFinal.Milliseconds())
			defer archivo.Close()
		}
	}
}
