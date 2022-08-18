import time
import numpy as np

def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2

    if l < n and arr[i] < arr[l]:
        largest = l

    if r < n and arr[largest] < arr[r]:
        largest = r

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)


def heapSort(arr):
    n = len(arr)

    for i in range(n//2, -1, -1):
        heapify(arr, n, i)

    for i in range(n-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)

if __name__ == '__main__':
    print("Algoritmo Heapsort")
    tamanios = [100,1000,2000,3000,4000,5000, 6000, 7000, 8000, 9000, 
						10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 
						90000, 100000, 110000, 120000,130000, 140000, 150000, 
						200000, 300000, 400000, 500000]
    pruebas = 11
    for tamanio in tamanios:
        for i in range (1,pruebas):
            array = np.loadtxt('1000000_random_numbers.txt', dtype=int,max_rows=tamanio)
            tiempoInicio = time.time()
            heapSort(array)
            tiempoFinal = time.time()
            milisengundos=(tiempoFinal-tiempoInicio)*1000
            segundos=tiempoFinal-tiempoInicio
            print(str(i) + ";" +  str(tamanio) + ";" +str(milisengundos).replace(".",","))   