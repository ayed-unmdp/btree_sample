#include <stdio.h>
#include <stdlib.h>

#include "queue.h"


// estructura auxiliar para implementar la cola
// nodo de listas dinámica simplmente enlazada
typedef struct _qnode {
  QUEUE_ELEM data;
  struct _qnode *next;
} qnode;

typedef struct _queue{
    qnode* head;        // puntero al frente de la cola
    qnode** tail;       // puntero al final de la cola
    int maxsize;      // tamaño máximo de la cola
    int count;        // cantidad de elementos en la cola
} queue;

// crear un nodo de lista
qnode* qnode_new(QUEUE_ELEM elem) {
  qnode* new_node = (qnode*) malloc(sizeof(qnode));

  new_node->data = elem;
  new_node->next = NULL;

  return new_node;
}

// liberar un nodo de lista
qnode* qnode_free(qnode* n) {
  qnode* r = n->next;
  free(n);
  return r;
}

// agregar un nodo al frente de la lista
void qnode_insert(qnode** list, qnode* n){
    n->next = *list;
    *list = n;    
}

// quitar el nodo al frente de la lista
qnode* qnode_remove(qnode** list){
    qnode* r = *list;
    *list = r->next;
    r->next = NULL;
    return r;
}

// obtener el valor del nodo
QUEUE_ELEM qnode_get(qnode* node){
    return node->data;
}

// crear un cola nueva
queue* queue_new(int maxsize){
    queue* q = (queue*) malloc(sizeof(queue));
    if (q != NULL) {
        q->head = NULL;
        q->tail = &q->head;
        q->maxsize = maxsize;
        q->count = 0;
    }
    return q;
}

// liberar la memoria de una cola vacía
void queue_free(queue* q){
    if (q != NULL) {
        free(q);
    }
}

// agregar un elemento a la cola
void enqueue(queue* q, QUEUE_ELEM elem){

    if (q->count >= q->maxsize) {
        printf("Queue overflow\n");
        exit(1);
    }

    qnode* new_node = qnode_new(elem);
    
    *q->tail = new_node;
    q->tail = &(new_node->next);
    q->count++;
}

// quitar un elemento de la cola
QUEUE_ELEM dequeue(queue* q){
    if (q->head == NULL) {
        printf("Queue underflow\n");
        exit(1);
    }

    qnode* aux = qnode_remove(&q->head);
    QUEUE_ELEM elem = qnode_get(aux);
    q->count--;
    
    if (q->head == NULL) {
        q->tail = &q->head; // resetea el tail cuando queda vacía
    }

    qnode_free(aux);
    return elem;
}

// obtener el elemento al frente de la cola
QUEUE_ELEM peek(queue* q){
    if (q->head == NULL) {
        printf("Queue is empty\n");
        exit(1);
    }
    
    return qnode_get(q->head);
}

// consultar si la cola está vacía
int queue_isempty(queue* q){
    return (q->count == 0);
}

// consultar si la cola está llena
int queue_isfull(queue* q){
    return (q->count == q->maxsize);
}

// obtener la cantidad de elementos en la cola
int queue_length(queue* q){
    return q->count;
}

// obtener el tamaño máximo de la cola
int queue_maxsize(queue* q){
    return q->maxsize;
}

// Eliminar todos los elementos de la cola y liberar la memoria
void queue_destroy(queue* q){
    if (q != NULL) {
        while (!queue_isempty(q)) {
            dequeue(q);
        }
        free(q);
    }
}