
#include <iostream>;

using namespace std;

//Primero definiremos una clase nodo para usar en la lista enlazada
template <class T> //Declaramos la clase como genérica
class node
{
    T value; //Cada nodo posee un valor genñerico

    public:
    node<T>* previous; //Tenemos un puntero al nodo anterior
    node<T>* next;     //Y al nodo siguiente 
    
    node<T>(T in_value) //Tenemos el constructor de la clase
    {
        this->value = in_value; //Guarda el valor en el nodo
        this->previous = NULL;
        this->next = NULL;
    }

    T Get_Value() //Mediante esta función devolvemos el valor
    {             //guardado en el nodo
        return this->value;
    }
};

//Aquí tenemos la lista enlazada que usa los nodos
template <class T>
class linked_list
{
    node<T>* first; //Tenemos punteros al primer
    node<T>* last;  //y al último nodo de la lista
    int count;      //Tenemos un contador que representa la cantidad de elementos

    //Mediante esta función podemos obtener un nodo a partir de su índice
    node<T>* At_Node(int index)
    {
        if (index < 0 || index >= count) //En caso de que esté fuera de los índices posibles
            return NULL;                 //retornamos NULL


    //La idea ahora será buscar el nodo desde first o desde last,
    //eligiendo entre estos dos al más cercano al nodo

        if (index <= count / 2) //En caso de que esté en la primera mitad
        {
            //Declaramos un puntero a nodo temporal para ir moviéndonos
            node<T>* temp = this->first;

            for (int i = 0; i <= index; i++) //Iteramos por posiciones
            {
                if (i == index) //Si encontramos al nodo lo devolvemos
                    return temp;
                else            //En otro caso pasamos al siquiente nodo
                    temp = temp->next; 
            }
        }
        else //En caso de que esté en la segunda mitad hacemos lo mismo, pero
        {    //en dirección contraria

            node<T>* temp = this->last;

            for (int i = this->count - 1; i >= 0; i--)
            {
                if (i == index)
                    return temp;
                else
                    temp = temp->previous;
            }
        }

        return NULL; //Retornamos NULL para evitar un error en tiempo
                     //de ejecución
    }

    public: //El resto de funciones son públicas

    linked_list<T>() //Aquí tenemos el constructor de la clase
    {
        this->count = 0;
        this->first = NULL;
        this->last = NULL;
    }

    //Redefinimos el operador =
    void operator =(linked_list<T> list) 
    {
        this->count = list.get_count;
        this->first = list->first;
        this->last = list->last;
    }

    //Mediante esta función, dado un índice, devolvemos el valor
    //en el nodo perteneciente a esa posición
    T At(int index)
    {
        return this->At_Node(index)->value;
    }

    //Mediante esta función añadimos un valor a la lista
    void Add_Last(T value)
    {
        if (this->count == 0) //En caso de que no tengamos elementos
            this->first = this->last = new node<T>(value);
        else
        {
            //Guardamos el valor en un nodo, y actualizamos los next
            //y previous de ese nodo y el anterior, y el last de la lista
            node<T>* temp = new node<T>(value);
            temp->previous = this->last;        
            this->last->next = temp;
            this->last = temp;
        }
        
        this->count = count + 1; //Aumentamos el contador de elementos
    }

    //Mediante esta función removemos el valor de la lista
    T Remove_Last()
    {
        if (this->count == 0) //Si no tenemos elementos no procedemos
            return NULL;

        node<T>* temp = this->last;  //Primero guardamos el last en un nodo temporal
        T value = temp->Get_Value(); //Guardamos el valor del nodo

        if (this->count == 1)    //Si solo tenemos un elemento
        {
            this->first = NULL; //Eliminamos el first y last
            this->last = NULL;
        }
        else //En otro caso
        {
            this->last = temp->previous; //Dejamos como last al penúltimo nodo
            this->last->next = NULL;     //Le quitamos el next al último nodo
        }

        this->count = this->count - 1; //Disminuimos el contador de la cantidad de elementos

        delete temp;  //Eliminamos dicho espacio en memoria
        return value; //Retornamos el valor
    }

    T Remove_At(int index)
    {
        //Si no es posible remover un elemento entonces no procedemos
        if (this->count == 0 || index < 0 || index >= this->count)
            return NULL;

        //Ahora creamos un nodo que será el que extraeremos más adelante,
        //y el valor que será extraído
        //Lo inicializamos en first para evitar el error de ejecución:
        //"potentialy uninitialized local pointer variable <pointer> used"
        node<T>* temp = this->first; 
        T value;

        if (count == 1)  //Si tenemos un solo elemento (y la posición es válida,
        {                //garantizado en el if anterior)
            temp = this->first;  //Guardamos el único elemento
            this->first = NULL;  //Eliminamos a first y last
            this->last = NULL;
        }

        if (index == 0 && count != 1) //En caso de que haya más de un elemento
        {                             //y se escoja el primero
            temp = this->first;               //Guardamos el primer elemento
            this->first = this->first->next;  //Ahora first será el 2do elemento
            this->first->previous = NULL;     //Eliminamos al previous de first
        }

        if (index == this->count -1 && count != 1) //En caso de que sea el último elemento
        {                                          //Y haya más de uno (garantizado en casos
            temp = this->last;                     //anteriores), hacemos lo mismo del
            this->last = this->last->previous;     //caso anterior pero con el last
            this->last->next = NULL;
        }

        if (index > 0 && index < this->count - 1 && count != 1) //En caso de que no sea
        {                                                       //el 1er ni último elemento
            temp = this->At_Node(index);           //Utilizamos a At_Node para buscar el nodo
            temp->previous->next = temp->next;     //Y conectamos al next y previous de ese nodo
            temp->next->previous = temp->previous;
        }

        this->count = this->count - 1; //Disminuimos el contador de la cantidad de elementos

        value = temp->Get_Value();     //Obtenemos el valor del nodo y lo separamos
        delete temp;                   //Eliminamos ese espacio en memoria
        return value; //Retornamos el valor
        
    }

    //Función que devuelve la cantidad de elementos que hay en la lista
    int Get_count()
    {
        return this->count;
    }

    //Función para imprimir todos los valores en la lista empezando por el primero
    void Print_Beging_First()
    {
        if (first != NULL) //Si hay al menos un elemento
        {
            for (node<T>* i = this->first; i != NULL; i = i->next) //Iteramos por los nodos
            {
                cout << i->Get_Value(); //Obtenemos su valor y lo imprimimos
                cout << "\n";
            }
        }
    }

    //Función para imprimir todos los valores en la lista empezando por el último
    void Print_Beging_Last()   //Hace lo mismo que la función anterior
    {                          //pero en orden inverso
        if (first != NULL)
        {
            for (node<T>* i = this->last; i != NULL; i = i->previous)
            {
                cout << i->Get_Value();
                cout << "\n";
            }
        }
    }

};

int main()
{    
    linked_list<int>* linked = new linked_list<int>();
    linked->Add_Last(1);
    linked->Add_Last(2);
    linked->Add_Last(3);
    linked->Add_Last(4);
    linked->Add_Last(5);
    linked->Add_Last(6);
    
    linked->Remove_At(5);

    linked->Print_Beging_First();
    cout << "\n";
    linked->Print_Beging_Last();


    return 0;
};
