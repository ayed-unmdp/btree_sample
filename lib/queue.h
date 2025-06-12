#define QUEUE_ELEM void*

typedef struct _queue queue;

// crear un cola nueva
queue* queue_new(int maxsize);

// liberar la memoria de una cola vacía
void queue_free(queue* s);

// agregar un elemento a la cola
void enqueue(queue* s, QUEUE_ELEM elem);

// quitar un elemento de la cola
QUEUE_ELEM dequeue(queue* s);

// obtener el elemento al frente de la cola
QUEUE_ELEM peek(queue* s);

// consultar si la cola está vacía
int queue_isempty(queue* s);

// consultar si la cola está llena
int queue_isfull(queue* s);

// obtener la cantidad de elementos en la cola
int queue_length(queue* s);

// obtener el tamaño máximo de la cola
int queue_maxsize(queue* s);

// Eliminar todos los elementos de la cola y liberar la memoria
void queue_destroy(queue* s);