#include <iostream>
#include <fstream>
#include <ctime> 

using namespace std;

void quicksort (int lista[], int primero, int ultimo);
int main()
{
	cout<<"Algoritmo Quicksort"<<endl;
	int tamanios[] = {100,1000,2000,3000,4000,5000, 6000, 7000, 8000, 9000, 
						10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 
						90000, 100000, 110000, 120000,130000, 140000, 150000, 
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
			ifstream archivo("C:\\Users\\Usuario\\go\\src\\ejm1\\1000000_random_numbers.txt");	
			archivo.is_open();
			int numero;
			int cont=0;
			while(archivo >> numero){
				lista[cont]=numero;
				if(cont==tamanio-1)break;
				cont++;
			}    
			clock_t tiempoInicio=clock();
			
			quicksort(lista,0,tamanio-1);

			clock_t tiempoFinal = clock();
			
			milesengundos = (double (tiempoFinal-tiempoInicio)/(CLOCKS_PER_SEC*1000));
			segundos = (double (tiempoFinal-tiempoInicio)/(CLOCKS_PER_SEC));
			printf("%i;%i;%f \n",j,tamanio,milesengundos);
			archivo.close();
		}
	}
}
void quicksort (int lista[], int primero, int ultimo){
	int i,j,central;
	central = (primero + ultimo)/2;
	double pivote =lista[central];
	
	i=primero;
	j=ultimo;
	
	while(i<=j){
		while(lista[i] < pivote){
			i++;
		}
		while(lista[j] > pivote){
			j--;
		}
		
		if(i <= j){
			double tmp;
			tmp = lista[i];
			lista[i]=lista[j];
			lista[j]=tmp;
			i++;
			j--;
		}				
	}
	
	if(primero < j)
		quicksort(lista,primero,j);
	if(i < ultimo)
		quicksort(lista,i,ultimo);
		
}
