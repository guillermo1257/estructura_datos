#include <iostream>
#include <fstream>
#include <stdlib.h>
#include<vector>
#include"time.h"

using namespace std;

void merge(int, int, int, vector<int>&);

void merge_sort(int izquierda, int derecha, vector<int> &array)
{
    int medio;
    if (izquierda < derecha)
    {
      
        medio = (izquierda + derecha) / 2;
        merge_sort(izquierda, medio, array);
        merge_sort(medio + 1, derecha, array);
        merge(izquierda, medio, derecha, array);
    }
}
void merge(int l, int m, int r, vector<int> &array)
{
    int *L;
    int *M;
    int n1 = m - l + 1;
    int n2 = r - m;

    L = new int[n1];
    M = new int[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = array[l + i];  //sub arrays1, posicion izquierda
    for (int j = 0; j < n2; j++)
        M[j] = array[m + 1 + j]; //sub array2, posicion del medio hacia adelante

    int i, j, k;
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2)
    {
        if (L[i] <= M[j])  //verificamos y vamos ordeando
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        array[k] = M[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] M;
}
void imprimir(vector<int> &array)
{
    int num = array.size();
    for (int i = 0; i <num; i++)
    {
        cout << array[i] << "   ";
    }
    cout<<endl;
}

int main() 
{
    vector<int>array;
    cout<<"Algoritmo MergeSort"<<endl;
    int tamanios[] = {100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
		10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000,
		90000, 100000, 110000, 120000, 130000, 140000, 150000,
		200000, 300000, 400000, 500000};
    int pruebas = 11;
    int tamPruebas = sizeof(tamanios) / sizeof(tamanios[0]);
    for (int k = 0; k < tamPruebas; k++) 
    {
      for (int j = 1; j < pruebas; j ++)
      {
        double segundos = 0.0;
        double milesengundos = 0.0;
        int tamanio=tamanios[k];
        int lista[tamanio-1];
        ifstream archivo("1000000_random_numbers.txt");	
        archivo.is_open();
        int numero;
        int cont=0;
        while(archivo >> numero){
          lista[cont]=numero;
          if(cont==tamanio-1)break;
          cont++;
        }    
        clock_t tiempoInicio=clock();
        
        for (int p = 0; p < tamanio; p++)
        {
            array.push_back(lista[p]);
        }
        
        merge_sort(0, tamanio, array);

        clock_t tiempoFinal = clock();
        
        milesengundos = (double (tiempoFinal-tiempoInicio)/(CLOCKS_PER_SEC*1000));
        segundos = (double (tiempoFinal-tiempoInicio)/(CLOCKS_PER_SEC));
        printf("%i;%i;%f \n",j,tamanio,milesengundos);
        archivo.close();
      }
    }
}