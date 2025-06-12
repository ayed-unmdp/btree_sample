#define STACK_ELEM int

typedef struct _stack stack;

// crear un pila nueva
stack* stack_new(int maxsize);

// liberar la memoria de una pila vacía
void stack_free(stack* s);

// agregar un elemento a la pila
void push(stack* s, STACK_ELEM elem);

// quitar un elemento de la pila
STACK_ELEM pop(stack* s);

// obtener el elemento al tope de la pila
STACK_ELEM top(stack* s);

// consultar si la pila está vacía
int stack_isempty(stack* s);

// consultar si la pila está llena
int stack_isfull(stack* s);

// obtener la cantidad de elementos en la pila
int stack_length(stack* s);

// obtener el tamaño máximo de la pila
int stack_maxsize(stack* s);

// Eliminar todos los elementos de la pila y liberar la memoria
void stack_destroy(stack* s);