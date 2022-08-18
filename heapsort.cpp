  #include <iostream>
  #include<windows.h>
  #include <fstream>
  
  #include <iomanip>
  using namespace std;
  
  void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    if (largest != i) {
      swap(arr[i], arr[largest]);
      heapify(arr, n, largest);
    }
  }
  
  void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
      swap(arr[0], arr[i]);
      heapify(arr, i, 0);
    }
  }
  
  void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
      cout << arr[i] << " ";
    cout << "\n";
  }
  
  int main() 
  {
    cout<<"Algoritmo heapsort"<<endl;
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
        
        heapSort(lista, tamanio-1);

        clock_t tiempoFinal = clock();
        
        milesengundos = (double (tiempoFinal-tiempoInicio)/(CLOCKS_PER_SEC*1000));
        segundos = (double (tiempoFinal-tiempoInicio)/(CLOCKS_PER_SEC));
        printf("%i;%i;%f \n",j,tamanio,milesengundos);
        archivo.close();
      }
    }
  }