
#include <iostream>;
#include <algorithm>; //Con esta biblioteca podemos usar el for_each 
#include <vector>; //Con esta biblioteca podemos usar la clase vector

using namespace std;

//Primero definiremos una clase nodo para usar en la lista enlazada
template <class T> //Declaramos la clase como genérica
class node
{
    T value; //Cada nodo posee un valor genérico

    public:
    using shared = shared_ptr<node<T>>;
    shared previous; //Tenemos un puntero al nodo anterior
    shared next;     //Y al nodo siguiente
    
    node<T>(T in_value) //Tenemos el constructor de la clase
    {
        this->value = in_value; //Guarda el valor en el nodo
        this->previous = nullptr;
        this->next = nullptr;
    }

    node<T>(const node<T> &other_node) //Tenemos el Constructor Copia de la clase
    {       
        this.value = other_node.value; //Copia los valores en vez de las referencias
        this.previous = other_node.previous;
        this.next = other_node.next;
    }

    node<T>(node<T>&& other_node) //Tenemos el Constructor Move de la clase
    {
        this.value = other_node.value; //Copia los valores en vez de las referencias
        this.previous = other_node.previous;
        this.next = other_node.next;

        other_node.value = NULL;       //Eliminamos los valores del nodo de entrada
        other_node.previous = nullptr;
        other_node.next = nullptr;
    }

    void operator =(node<T> new_node) //Sobrecarga del operador =
    {
        this->value = new_node->Get_Value;
        this->previous = new_node->previous;
        this->next = new_node->next;
    }

    //Destructor de la clase
    ~node() = default;
        
    T Get_Value() //Mediante esta función devolvemos el valor
    {             //guardado en el nodo
        return this->value;
    }
};

//Aquí tenemos la lista enlazada que usa los nodos
template <class T>
class linked_list
{
    shared_ptr<node<T>> first; //Tenemos punteros al primer
    shared_ptr<node<T>> last;  //y al último nodo de la lista
    int count;      //Tenemos un contador que representa la cantidad de elementos

    //Mediante esta función podemos obtener un nodo a partir de su índice
    shared_ptr<node<T>> At_Node(int index)
    {
        if (index < 0 || index >= count) //En caso de que esté fuera de los índices posibles
            return nullptr;                 //retornamos NULL


    //La idea ahora será buscar el nodo desde first o desde last,
    //eligiendo entre estos dos al más cercano al nodo

        if (index <= count / 2) //En caso de que esté en la primera mitad
        {
            //Declaramos un puntero a nodo temporal para ir moviéndonos
            shared_ptr<node<T>> temp = this->first;

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

            shared_ptr<node<T>> temp = this->last;

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
        this->first = nullptr;
        this->last = nullptr;
    }

    linked_list<T>(const linked_list<T> &other_list) //Aquí tenemos el Constructor Copia de la clase
    {
        this.count = other_list.count;
        this.first = other_list.first;
        this.last = other_list.last;
    }

    linked_list<T>(linked_list<T>&& other_list) //Aquí tenemos el Constructor Move de la clase
    {
        this.count = other_list.count;
        this.first = other_list.first;
        this.last = other_list.last;

        other_list.count = 0;
        other_list.first = nullptr;
        other_list.last = nullptr;
    }

    //Redefinimos el operador =
    void operator =(linked_list<T> list) 
    {
        this->count = list.get_count;
        this->first = list->first;
        this->last = list->last;
    }

    //Constructor a partir de List_Inicialization
    linked_list(initializer_list<T> in_list)
    { 
        this->count = 0;
        this->first = nullptr;
        this->last = nullptr;
      //Con for_each vamos por todos los elementos de la lista
      //y mediante una función lambda los agregamos
        for_each(in_list.begin(), in_list.end(), [this](T i) {this->Add_Last(i);} );
    }

    //Constructor a partir de un vector<T>
    linked_list(vector<T> in_vector)
    {
        this->count = 0;
        this->first = nullptr;
        this->last = nullptr;
        //Con for_each vamos por todos los elementos del vector
        //y mediante una función lambda los agregamos
        for_each(in_vector.begin(), in_vector.end(), [this](T i) {this->Add_Last(i); });
    }

    //Destructor de la clase
    ~linked_list() = default;

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
            this->first = this->last = shared_ptr<node<T>>(new node<T>(value));
        else
        {
            //Guardamos el valor en un nodo, y actualizamos los next
            //y previous de ese nodo y el anterior, y el last de la lista
            
            shared_ptr<node<T>> temp = shared_ptr<node<T>>(new node<T>(value));
            temp->previous = this->last;        
            this->last->next = temp;
            this->last = temp;
        }
        
        this->count = count + 1; //Aumentamos el contador de elementos
    }

    //Mediante esta función removemos el valor de la lista
    T Remove_Last() noexcept(true)
    {
        if (this->count == 0) //Si no tenemos elementos no procedemos
            return NULL;

        shared_ptr<node<T>> temp = this->last;  //Primero guardamos el last en un nodo temporal
        T value = temp->Get_Value(); //Guardamos el valor del nodo

        if (this->count == 1)    //Si solo tenemos un elemento
        {
            this->first = nullptr; //Eliminamos el first y last
            this->last = nullptr;
        }
        else //En otro caso
        {
            this->last = temp->previous; //Dejamos como last al penúltimo nodo
            this->last->next = nullptr;     //Le quitamos el next al último nodo
        }

        this->count = this->count - 1; //Disminuimos el contador de la cantidad de elementos

        return value; //Retornamos el valor
    }

    T Remove_At(int index) noexcept(true)
    {
        //Si no es posible remover un elemento entonces no procedemos
        if (this->count == 0 || index < 0 || index >= this->count)
            return NULL;

        //Ahora creamos un nodo que será el que extraeremos más adelante,
        //y el valor que será extraído
        //Lo inicializamos en first para evitar el error de ejecución:
        //"potentialy uninitialized local pointer variable <pointer> used"
        shared_ptr<node<T>> temp = this->first;
        T value;

        if (count == 1)  //Si tenemos un solo elemento (y la posición es válida,
        {                //garantizado en el if anterior)
            temp = this->first;  //Guardamos el único elemento
            this->first = nullptr;  //Eliminamos a first y last
            this->last = nullptr;
        }

        if (index == 0 && count != 1) //En caso de que haya más de un elemento
        {                             //y se escoja el primero
            temp = this->first;               //Guardamos el primer elemento
            this->first = this->first->next;  //Ahora first será el 2do elemento
            this->first->previous = nullptr;     //Eliminamos al previous de first
        }

        if (index == this->count -1 && count != 1) //En caso de que sea el último elemento
        {                                          //Y haya más de uno (garantizado en casos
            temp = this->last;                     //anteriores), hacemos lo mismo del
            this->last = this->last->previous;     //caso anterior pero con el last
            this->last->next = nullptr;
        }

        if (index > 0 && index < this->count - 1 && count != 1) //En caso de que no sea
        {                                                       //el 1er ni último elemento
            temp = this->At_Node(index);           //Utilizamos a At_Node para buscar el nodo
            temp->previous->next = temp->next;     //Y conectamos al next y previous de ese nodo
            temp->next->previous = temp->previous;
        }

        this->count = this->count - 1; //Disminuimos el contador de la cantidad de elementos

        value = temp->Get_Value();     //Obtenemos el valor del nodo y lo separamos
        return value; //Retornamos el valor
        
    }

    

    //Función que devuelve la cantidad de elementos que hay en la lista
    int length()
    {
        return this->count;
    }

    //Puntero a función de cantidad variable de argumentos, que devuelve
    template<typename R, typename... T>
    using Alias_Function = R (*)(T...);

    //Función que transforma todos los elementos de una linked_list<T> a una linked_list<R>
    template<typename R, typename T>
    linked_list<R> Map(Alias_Function<R, T> Transformation_Funtion) //Recibe la función de transformación
    {
        linked_list<R> out_list = linked_list(); //Creamos la función que devolveremos

        for (node<T> i = this->first; i != nullptr; i = i->next)
        {   //Vamos por todos los nodos de nuestra lista
            
            //Añadimos todos los nodos transformados a la nueva lista
            out_list.Add_Last(Transformation_Funtion(i->Get_Value()));
        }

        return out_list; //Devolvemos la lista
    }


    //Función para imprimir todos los valores en la lista empezando por el primero
    void Print_Starting_First()
    {
        if (first != nullptr) //Si hay al menos un elemento
        {
            for (shared_ptr<node<T>> i = this->first; i != nullptr; i = i->next) //Iteramos por los nodos
            {
                cout << i->Get_Value(); //Obtenemos su valor y lo imprimimos
                cout << "\n";
            }
        }
    }

    //Función para imprimir todos los valores en la lista empezando por el último
    void Print_Starting_Last()  //Hace lo mismo que la función anterior
    {                          //pero en orden inverso
        if (first != nullptr)
        {
            for (shared_ptr<node<T>> i = this->last; i != nullptr; i = i->previous)
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
    linked->Remove_At(2);
    linked->Remove_Last();

    linked->Print_Starting_First();
    cout << "\n";
    linked->Print_Starting_Last();

    linked_list<int>* linked_b = linked;

    linked_list<int> linked_c = { 1,2,3,4 };

    cout << "\n";
    linked_c.Print_Starting_First();
    cout << "\n";
    linked_c.Print_Starting_Last();

    cout << "\n";
    linked_list<int>* a = new linked_list<int>(vector<int>({ 1,2,3,4,5 }));
    a->Print_Starting_First();
    return 0;
};
