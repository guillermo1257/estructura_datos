import time
import numpy as np

def iniciarDatos():
    print("Algoritmo Quicksort")
    tamanios = [100,1000,2000,3000,4000,5000, 6000, 7000, 8000, 9000, 
                10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 
                90000, 100000, 110000, 120000,130000, 140000, 150000, 
                200000, 300000, 400000, 500000]
    pruebas = 11
    for tamanio in tamanios:
        for i in range (1,pruebas):
            archivo = np.loadtxt('1000000_random_numbers.txt', dtype=int,max_rows=tamanio)
            tiempoInicio = time.time()
            quicksort(archivo,0,tamanio-1)
            tiempoFinal = time.time()
            milisengundos=(tiempoFinal-tiempoInicio)*1000
            segundos=tiempoFinal-tiempoInicio
            print(str(i) + ";" +  str(tamanio) + ";" +str(milisengundos).replace(".",","))         

def quicksort(lista, primero, ultimo):
    central=int((primero + ultimo)/2)
    pivote=lista[central]
    i=primero
    j=ultimo

    while i <= j:
        while lista[i] < pivote:
            i+=1
        while lista[j] > pivote:
            j-=1

        if i <= j:
            tmp = lista[i]
            lista[i] = lista[j]
            lista[j] = tmp
            i+=1
            j-=1
    
    if primero < j:
        quicksort(lista,primero,j)
    if i < ultimo:
        quicksort(lista,i,ultimo)     

iniciarDatos()