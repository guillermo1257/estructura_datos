/* El siguiente programa contiene la implementacion del 
algoritmo B-Tree que tiene métodos de busqueda, insertar, remover, minimo y maximo.
https://www.geeksforgeeks.org/b-tree-set-1-introduction-2/
  
   La función de eliminación se ha compartimentado en 8 funciones para facilitar
   de entendimiento y claridad
  
   Las siguientes funciones son exclusivas para la eliminación
   En la clase BTreeNode:
    1) remove
    2) removeFromLeaf
    3) removeFromNonLeaf
    4) getPred
    5) getSucc
    6) borrowFromPrev
    7) borrowFromNext
    8) merge
    9) findKey
  
   En la clase BTree:
     1) remove
  
  La eliminación de una clave de un B-Tree es un proceso bastante complicado. El programa maneja
  los 6 casos diferentes que pueden surgir al retirar una clave. 
*/

#include<iostream>
using namespace std;
  
// A BTree node
class BTreeNode
{
    int *keys;  // Array de claves
    int t;      // Grado minimo rango para el numero de claves
    BTreeNode **C; // puntero de array secundarios o hijos
    int n;     // Numero de claves
    bool leaf; // True cuando el nodo es hoja 
  
public:
  
    BTreeNode(int _t, bool _leaf);   // Constructor
  
    // Funcion para recorrer los nodos
    void traverse();
  
    // Funcion para buscar una clave 
    BTreeNode *search(int k);   // retorna NULL si k no esta presente
  
    // Funcion que devuelve la clave que es mayor
    // o igual a k
    int findKey(int k);
  
    // insertar una nueva clave en el subarbol de este nodo. 
    //La suposición es que el nodo no debe estar lleno cuando se llama a esta función    
    void insertNonFull(int k);
  
   // Para dividir el hijo y de este nodo. i es el índice de y en la matriz secundaria C[]. 
   //El hijo y debe estar lleno cuando se llama a esta función
    void splitChild(int i, BTreeNode *y);
  
    // para eliminar la clave k en el subárbol enraizado con este nodo
    void remove(int k);
  
    // Eliminar la clave presente en la posición idx-ésima en este nodo que es una hoja
    void removeFromLeaf(int idx);
  
    // Eliminar la clave presente en la posición idx-ésima en este nodo que no es un nodo de hoja
    void removeFromNonLeaf(int idx);
  
    // Obtener el predecesor de la clave, donde la clave está presente en la posición idx-ésima en el nodo
    int getPred(int idx);
  
    // obtener el sucesor de la clave, donde la clave está presente en la posición idx-ésima en el nodo
    int getSucc(int idx);
  
    // llenar el nodo secundario presente en la posición idx-ésima en la matriz C[] si ese elemento secundario tiene menos de t-1 claves
    void fill(int idx);
  
    // tomar prestada una clave del nodo C[idx-1]-th y colocarla en el nodo C[idx]th
    void borrowFromPrev(int idx);
  
    //tomar prestada una clave del nodo C[idx+1]-th y colocarla en el nodo C[idx]th
    void borrowFromNext(int idx);
  
    //fusionar idx-th child del nodo con (idx+1)th child del nodo
    void merge(int idx);
  
    // acceder a miembros privados de esta clase en las funciones de BTree
    friend class BTree;
};
  
class BTree
{
    BTreeNode *root; // Puntero al nodo raíz
    int t;  // Grado Mínimo
public:
  
    // Contructor incial (empty)
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }
  
    void traverse()
    {
        if (root != NULL) root->traverse();
    }
  
    // buscar una clave en el árbol
    BTreeNode* search(int k)
    {
        return (root == NULL)? NULL : root->search(k);
    }
  
    // inserta una nueva clave en este B-Tree
    void insert(int k);
  
    // elimina una nueva clave en este B-Tree
    void remove(int k);

    // obetner el minimo de B-Tree
    int min();

    // obtener el maximo de B-Tree
    int max();
  
};
  
BTreeNode::BTreeNode(int t1, bool leaf1)
{
    // Copia el grado mínimo dado y la propiedad de la hoja.
    t = t1;
    leaf = leaf1;
  
    // Asigna memoria para el número máximo de claves posibles y punteros secundarios
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];
  
    // Initialize the number of keys as 0
    n = 0;
}
  
// devuelve el índice de la primera clave que es mayor o igual que k
int BTreeNode::findKey(int k)
{
    int idx=0;
    while (idx<n && keys[idx] < k)
        ++idx;
    return idx;
}
  
// eliminar la clave k del subárbol enraizado con este nodo
void BTreeNode::remove(int k)
{
    int idx = findKey(k);
  
    // La clave que se eliminará está presente en este nodo.
    if (idx < n && keys[idx] == k)
    {
  
        // Si el nodo es un nodo hoja, se llama a removeFromLeaf De lo contrario, se llama a la función removeFromNonLeaf
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {
  
        // Si este nodo es un nodo hoja, entonces la clave no está presente en el árbol
        if (leaf)
        {
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }
  
        // La clave que se eliminará está presente en el subárbol enraizado con este nodo 
        // La bandera indica si la clave está presente en el subárbol enraizado con el último hijo de este nodo
        bool flag = ( (idx==n)? true : false );
  
        // Si el nodo hijo donde se supone que existe la clave tiene menos de t claves, llenamos ese nodo hijo
        if (C[idx]->n < t)
            fill(idx);
  
        //Si el último hijo se ha fusionado, debe haberse fusionado con el hijo anterior, por lo que recurrimos al (idx-1) hijo. 
        //De lo contrario, recurrimos al (idx)th hijo que ahora tiene al menos t claves
        if (flag && idx > n)
            C[idx-1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}
  
// eliminar la clave idx-th de este nodo, que es un nodo hoja
void BTreeNode::removeFromLeaf (int idx)
{
  
    // Mueva todas las claves después de la posición idx-th un lugar hacia atrás
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];
  
    // Reducir el conteo de claves
    n--;
  
    return;
}
  
// eliminar la clave idx-th de este nodo, que es un nodo que no es hoja
void BTreeNode::removeFromNonLeaf(int idx)
{
  
    int k = keys[idx];
  
    // Si el hijo que precede a k (C[idx]) tiene al menos t claves, busque el predecesor 'pred' de k en el subárbol con raíz en C[idx]. 
    // Reemplace k por pred. Eliminar recursivamente pred en C[idx]
    if (C[idx]->n >= t)
    {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }
  
    // Si el hijo C[idx] tiene menos de t claves, examine C[idx+1]. Si C[idx+1] tiene al menos t claves, encuentre el sucesor 'succ' de k en el subárbol enraizado en C[idx+1] 
    //Reemplace k por succ Recursivamente elimine succ en C[idx+1]
    else if  (C[idx+1]->n >= t)
    {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx+1]->remove(succ);
    }
  
    // Si tanto C[idx] como C[idx+1] tienen menos de t claves, combine k y todo C[idx+1] en C[idx] 
    //Ahora C[idx] contiene 2t-1 claves C[idx+ gratis 1] y elimine recursivamente k de C[idx]
    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}
  
// obtener el predecesor de las claves [idx]
int BTreeNode::getPred(int idx)
{
    // sigue moviéndote hacia el nodo más a la derecha hasta que lleguemos a una hoja
    BTreeNode *cur=C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
  
    // Devolver la última clave de la hoja.
    return cur->keys[cur->n-1];
}
 /*********************************************************************************************************************/ 
int BTreeNode::getSucc(int idx)
{
  
    // Siga moviendo el nodo más a la izquierda comenzando desde C[idx+1] hasta llegar a una hoja
    BTreeNode *cur = C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];
  
    // Devuelve la primera clave de la hoja.
    return cur->keys[0];
}
  
// para llenar el hijo C[idx] que tiene menos de t-1 claves
void BTreeNode::fill(int idx)
{
  
    // Si el hijo anterior (C[idx-1]) tiene más de t-1 claves, tome prestada una clave de ese hijo
    if (idx!=0 && C[idx-1]->n>=t)
        borrowFromPrev(idx);
  
    // Si el siguiente hijo(C[idx+1]) tiene más de t-1 llaves, toma prestada clave de ese hijo
    else if (idx!=n && C[idx+1]->n>=t)
        borrowFromNext(idx);
  
    //Fusionar C[idx] con su hermano Si C[idx] es el último hijo, 
    //fusionarlo con su hermano anterior De lo contrario, fusionarlo con su próximo hermano
    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}
  
// Una función para tomar prestada una clave de C[idx-1] e insertarla en C[idx]
void BTreeNode::borrowFromPrev(int idx)
{
  
    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx-1];
  
    // La última clave de C[idx-1] sube al padre y la clave[idx-1] del padre se inserta como la primera clave en C[idx]. 
    // Por lo tanto, el hermano pierde una clave y el hijo gana una clave
  
    // Mover todas las claves en C[idx] un paso adelante
    for (int i=child->n-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];
  
    // Si C[idx] no es una hoja, mueva todos sus punteros secundarios un paso adelante
    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }
  
    // Configuración de la primera clave del hijo igual a las claves [idx-1] del nodo actual
    child->keys[0] = keys[idx-1];
  
    // Mover al último hijo del hermano como primer hijo de C[idx]
    if(!child->leaf)
        child->C[0] = sibling->C[sibling->n];
  
    // Mover la clave del hermano al padre
    //  Esto reduce el número de claves en el hermano.
    keys[idx-1] = sibling->keys[sibling->n-1];
  
    child->n += 1;
    sibling->n -= 1;
  
    return;
}
  
// tomar prestada una clave de C[idx+1] y colocarla en C[idx]
void BTreeNode::borrowFromNext(int idx)
{
  
    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx+1];
  
    // keys[idx] se inserta como la última clave en C[idx]
    child->keys[(child->n)] = keys[idx];
  
    // El primer hijo del hermano se inserta como el último hijo en C[idx]
    if (!(child->leaf))
        child->C[(child->n)+1] = sibling->C[0];
  
    //La primera clave del hermano se inserta en las claves [idx]
    keys[idx] = sibling->keys[0];
  
    // Moviendo todas las llaves hermano un paso atrás
    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];
  
    // Mover los punteros secundarios un paso atrás
    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }
  
    // Aumentar y disminuir el número de claves de C[idx] y C[idx+1] respectivamente
    child->n += 1;
    sibling->n -= 1;
  
    return;
}
  
// fusionar C[idx] con C[idx+1] C[idx+1] se libera después de la fusión
void BTreeNode::merge(int idx)
{
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx+1];
  
    //Extraer una clave del nodo actual e insertarla en la posición (t-1) de C[idx]
    child->keys[t-1] = keys[idx];
  
    // Copiando las claves de C[idx+1] a C[idx] al final
    for (int i=0; i<sibling->n; ++i)
        child->keys[i+t] = sibling->keys[i];
  
    // Copiando los punteros secundarios de C[idx+1] a C[idx]
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->n; ++i)
            child->C[i+t] = sibling->C[i];
    }
  
    //Mover todas las claves después de idx en el nodo actual un paso antes: 
    //para llenar el espacio creado al mover claves [idx] a C [idx]
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];
  
    // Mover los punteros secundarios después de (idx+1) en el nodo actual un paso antes
    for (int i=idx+2; i<=n; ++i)
        C[i-1] = C[i];
  
    // Actualización del recuento de claves del hijo y el nodo actual
    child->n += sibling->n+1;
    n--;
  
    // Liberando la memoria ocupada por el hermano
    delete(sibling);
    return;
}
  
// La función principal que inserta una nueva clave en este B-Tree
void BTree::insert(int k)
{
    // Si el árbol está vacío
    if (root == NULL)
    {
        // Asignar memoria para root
        root = new BTreeNode(t, true);
        root->keys[0] = k;  // Insertar clave
        root->n = 1;  // Actualizar el número de claves en la raíz
    }
    else // Si el árbol no está vacío
    {
        // Si la raíz está llena, entonces el árbol crece en altura.
        if (root->n == 2*t-1)
        {
            // Asignar memoria para la nueva raíz
            BTreeNode *s = new BTreeNode(t, false);
  
            // Hacer la raíz como hija de nueva raíz
            s->C[0] = root;
  
            // Divida la raíz anterior y mueva 1 clave a la nueva raíz
            s->splitChild(0, root);
  
            //New root tiene dos hijos ahora. Decide cuál de los dos hijos va a tener llave nueva
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
  
            // Cambiar raíz
            root = s;
        }
        else  // Si la raíz no está llena, llame a insertNonFull para la raíz
            root->insertNonFull(k);
    }
}
  
//  insertar una nueva clave en este nodo La suposición es que el nodo no debe estar lleno cuando se llama a esta función
void BTreeNode::insertNonFull(int k)
{
    // Inicializar índice como índice del elemento más a la derecha
    int i = n-1;
  
    // Si este es un nodo hoja
    if (leaf == true)
    {
        // El siguiente ciclo hace dos cosas 
        // a) Encuentra la ubicación de la nueva clave que se insertará 
        // b) Mueve todas las claves mayores a un lugar más adelante
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }
  
        // Inserte la nueva clave en la ubicación encontrada
        keys[i+1] = k;
        n = n+1;
    }
    else // Si este nodo no es hoja
    {
        // Encuentra al hijo que va a tener la nueva clave
        while (i >= 0 && keys[i] > k)
            i--;
  
        // A ver si el hijo encontrado está llena
        if (C[i+1]->n == 2*t-1)
        {
            // Si el hijo está lleno, entonces divídalo.
            splitChild(i+1, C[i+1]);
  
            // Después de la división, la clave central de C[i] sube y C[i] se divide en dos. 
            // Mira cuál de los dos va a tener la nueva clave
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}
  
// dividir el hijo y de este nodo Tenga en cuenta que debe estar lleno cuando se llama a esta función
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    // Cree un nuevo nodo que almacenará (t-1) claves de y
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
  
    // Copie las últimas claves (t-1) de y a z
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];
  
    // Copie los últimos t hijos de y a z
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
  
    // Reducir el número de claves en y
    y->n = t - 1;
  
    // Dado que este nodo va a tener un nuevo hijo,
    // Crear espacio de nuevo hijo
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
  
    // Vincular el nuevo hijo a este nodo
    C[i+1] = z;
  
    // Una calve de y se moverá a este nodo. 
    // Encuentre la ubicación de la nueva clave y mueva todas las claves mayores un espacio hacia adelante
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
  
    // Copie la clave central de y en este nodo
    keys[i] = y->keys[t-1];
  
    // Incrementar el conteo de claves en este nodo
    n = n + 1;
}
  
// Función para recorrer todos los nodos en un subárbol enraizado con este nodo
void BTreeNode::traverse()
{
    // Hay n claves y n+1 hijos, atraviesan n claves y los primeros n hijos
    int i;
    for (i = 0; i < n; i++)
    {        
        // Si esto no es una hoja, antes de imprimir la clave [i], recorra el subárbol enraizado con el hijo C [i].
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }
  
    // Imprime el subárbol enraizado con el último hijo
    if (leaf == false)
        C[i]->traverse();
}
  
// Función para buscar la clave k en el subárbol enraizado con este nodo
BTreeNode *BTreeNode::search(int k)
{
    // Encuentra la primera clave mayor o igual a k
    int i = 0;
    while (i < n && k > keys[i])
        i++;
  
    // Si la clave encontrada es igual a k, devuelve este nodo
    if (keys[i] == k)
        return this;
  
    // Si la clave no se encuentra aquí y este es un nodo hoja
    if (leaf == true)
        return NULL;
  
    // Ir al hijo apropiado
    return C[i]->search(k);
}

// Funcion que devuelve la clave menor de B-Tree
int BTree::min()
{    
    // Siga moviendo el nodo más a la izquierda comenzando desde C[idx+1] hasta llegar a una hoja    
    BTreeNode *tmp = root;
    while (!tmp->leaf)
        tmp = tmp->C[0];
  
    // Devuelve la primera clave de la hoja.
    return tmp->keys[0];
    
}

//Funcion que devuelve la clave mayor del B-Tree
int BTree::max()
{
    // sigue moviéndote hacia el nodo más a la derecha hasta que lleguemos a una hoja
    BTreeNode *tmp=root;
    while (!tmp->leaf)
        tmp = tmp->C[tmp->n];
  
    // Devolver la última clave de la hoja.
    return tmp->keys[tmp->n-1];
}
  
void BTree::remove(int k)
{
    if (!root)
    {
        cout << "el arbol esta vacio \n";
        return;
    }
  
    // Llame a la función de eliminar para root
    root->remove(k);
  
        // Si el nodo raíz tiene 0 claves, haga que su primer hijo sea la nueva raíz si tiene un hijo; 
        // de lo contrario, establezca la raíz como NULL
    if (root->n==0)
    {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];
  
        // Libera la raíz que se elimina
        delete tmp;
    }
    return;
}    

int main()
{
    BTree t(3); // Un B-Tree con grado mínimo 3
    int val, opt;
    while (true) {
        cout<<"1. Insertar \t2. Eliminar\n";
        cout<<"3. Buscar \t4. Mostrar recorrido\n";
        cout<<"5. Minimo \t6. Maximo\n";
        cout<<"7. Salir \nSelecciona una opcion: ";
        cin >> opt;
        cout << endl;
        switch (opt) {
        case 1:
            cout<<"Ingresa un numero: ";
            cin >> val;
            t.insert(val);
            break;
        case 2:
            cout<<"Ingresa un numero a eliminar: ";
            cin>>val;
            t.remove(val);
            break;
        case 3:
            cout<<"Ingrese el numero a buscar: ";
            cin>>val;
            (t.search(val) != NULL)? cout << "\nEncontrado" : cout << "\nNo Encontrado";
            break;
        case 4:
            t.traverse();
            cout<<endl;
            break;
        case 5:            
            cout<<t.min()<<endl;
            break;
        case 6:
            cout<<t.max()<<endl;
            break;
        case 7:
            exit(0);            
        }
        cout<<endl;
    }
    system("pause");
}