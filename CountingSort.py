# Python programa algoritno de counting sort
# incluye para numeros negativos
import time
import numpy as np
 
# Funcion que ordena el array de datos
def count_sort(arr):
    max_element = int(max(arr))
    min_element = int(min(arr))
    range_of_elements = max_element - min_element + 1

    # Crea el array de conteo para almacenar la frecuencia de cada elemento    
    count_arr = [0 for _ in range(range_of_elements)]
    output_arr = [0 for _ in range(len(arr))]
 
    # Guarda la frecuencia de cada elemento
    for i in range(0, len(arr)):
        count_arr[arr[i]-min_element] += 1
 
    # Modfica array para que contenga la posicion en la salida 
    for i in range(1, len(count_arr)):
        count_arr[i] += count_arr[i-1]
 
    # Construye el array de salida
    for i in range(len(arr)-1, -1, -1):
        output_arr[count_arr[arr[i] - min_element] - 1] = arr[i]
        count_arr[arr[i] - min_element] -= 1
 
    # Copia el array de salida en el original para contenga elementos ordenados
    for i in range(0, len(arr)):
        arr[i] = output_arr[i]
 
    return arr
def printArray(arr):
    for i in arr:
        print(i)
if __name__ == '__main__':
    print("Algoritmo CountingSort")
    tamanios = [100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
		10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000,
		90000, 100000, 110000, 120000, 130000, 140000, 150000,
		200000, 300000, 400000, 500000]
    pruebas = 11
    for tamanio in tamanios:
        for i in range (1,pruebas):
            archivo = np.loadtxt('1000000_random_numbers.txt', dtype=int,max_rows=tamanio)
            tiempoInicio = time.time()
            count_sort(archivo)
            tiempoFinal = time.time()
            milisengundos=(tiempoFinal-tiempoInicio)*1000
            segundos=tiempoFinal-tiempoInicio
            print(str(i) + ";" +  str(tamanio) + ";" +str(milisengundos).replace(".",","))   