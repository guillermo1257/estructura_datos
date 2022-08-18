// Counting sort incluye números negativos
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
 
void countSort(vector<int>& arr)
{
    int max = *max_element(arr.begin(), arr.end());
    int min = *min_element(arr.begin(), arr.end());
    int range = max - min + 1;
 
    vector<int> count(range), output(arr.size());
    for (int i = 0; i < arr.size(); i++)
        count[arr[i] - min]++;
 
    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];
 
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
 
    for (int i = 0; i < arr.size(); i++)
        arr[i] = output[i];
}
 
void printArray(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << "\n";
}
int main() 
{
    vector<int>array;
    cout<<"Algoritmo CountingSort"<<endl;
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
        while(archivo >> numero)
        {
          lista[cont]=numero;
          if(cont==tamanio-1)break;
          cont++;
        }    
        clock_t tiempoInicio=clock();
        
        for (int p = 0; p < tamanio; p++)
        {
            array.push_back(lista[p]);
        }
        
        countSort(array);

        clock_t tiempoFinal = clock();
        
        milesengundos = (double (tiempoFinal-tiempoInicio)/(CLOCKS_PER_SEC*1000));
        segundos = (double (tiempoFinal-tiempoInicio)/(CLOCKS_PER_SEC));
        printf("%i;%i;%f \n",j,tamanio,milesengundos);
        archivo.close();
      }
    }
}