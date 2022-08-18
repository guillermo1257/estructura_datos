import time
import numpy as np

def mergeSort(array):
    if len(array) > 1:

        #  dividimos el array en sub-arrays
        medio = len(array)//2 #partimos por la mitad(medio)
        izquierda = array[:medio]
        derecha = array[medio:]

        # llamada recursiva para dividir los sub-arrays
        mergeSort(izquierda)
        mergeSort(derecha)

        i = j = k = 0

        while i < len(izquierda) and j < len(derecha):
            if izquierda[i] < derecha[j]:
                array[k] = izquierda[i]
                i += 1
            else:
                array[k] = derecha[j]
                j += 1
            k += 1

        # recorremos los elementos restantes y los agregamos en el array
        while i < len(izquierda):
            array[k] = izquierda[i]
            i += 1
            k += 1

        while j < len(derecha):
            array[k] = derecha[j]
            j += 1
            k += 1


# Print the array
def printList(array):
    tam=len(array)
    for i in range(len(array)):
        print(array[i],end=" ")

 
if __name__ == '__main__':
    print("Algoritmo Mergesort")
    tamanios = [100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
		10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000,
		90000, 100000, 110000, 120000, 130000, 140000, 150000,
		200000, 300000, 400000, 500000]
    pruebas = 11
    for tamanio in tamanios:
        for i in range (1,pruebas):
            array = np.loadtxt('1000000_random_numbers.txt', dtype=int,max_rows=tamanio)
            tiempoInicio = time.time()
            mergeSort(array)
            tiempoFinal = time.time()
            milisengundos=(tiempoFinal-tiempoInicio)*1000
            segundos=tiempoFinal-tiempoInicio
            print(str(i) + ";" +  str(tamanio) + ";" +str(milisengundos).replace(".",","))       
  
   