#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// estructura auxiliar para implementar la pila 
// nodo de listas dinámica simplmente enlazada
typedef struct _node {
  STACK_ELEM data;
  struct _node *next;
} node;

// crear un nodo de lista
node* node_new(STACK_ELEM elem) {
  node* new_node = (node*) malloc(sizeof(node));

  new_node->data = elem;
  new_node->next = NULL;

  return new_node;
}

// liberar un nodo de lista
node* node_free(node* n) {
  node* r = n->next;
  free(n);
  return r;
}

// agregar un nodo al frente de la lista
void node_insert(node** list, node* n){
    n->next = *list;
    *list = n;    
}

// quitar el nodo al frente de la lista
node* node_remove(node** list){
    node* r = *list;
    *list = r->next;
    r->next = NULL;
    return r;
}

// obtener el valor del nodo
STACK_ELEM node_get(node* node){
    return node->data;
}

/* IMPLEMENTACIÓN DINÁMICA DE STACK */
// estructura de la pila
typedef struct _stack {
  node *top;
  int maxsize;
  int count;
} stack;

// crear una pila nueva
stack* stack_new(int maxsize) {
  stack* s = (stack*) malloc(sizeof(stack));

  s->top = NULL;
  s->maxsize = maxsize;
  s->count = 0;

  return s;
}

// liberar la memoria de una pila vacía
void stack_free(stack* s) {
  if (!stack_isempty(s)) {
    printf("Stack not empty\n");
    exit(1);
  }

  free(s);
}

// consultar si la pila está vacía
int stack_isempty(stack* s) {
  return (s->count == 0);
}

// consultar si la pila está llena
int stack_isfull(stack* s) {
  return (s->count == s->maxsize);
}

// agregar un elemento a la pila
void push(stack* s, STACK_ELEM elem) {
  if (stack_isfull(s)) {
    printf("Stack overflow\n");
    exit(1);
  }
  
  node_insert(&s->top, node_new(elem));
  s->count++;
}

// quitar un elemento de la pila
STACK_ELEM pop(stack* s) {
  if (stack_isempty(s)) {
    printf("Stack underflow\n");
    exit(1);
  }

  node *aux = node_remove(&s->top);
  STACK_ELEM elem = node_get(aux);
  s->count--;
  node_free(aux);
  return elem;
}

// obtener el elemento al tope de la pila
STACK_ELEM top(stack* s) {
  if (stack_isempty(s)) {
    printf("Stack underflow\n");
    exit(1);
  }

  return node_get(s->top);
}

// obtener la cantidad de elementos en la pila
int stack_length(stack* s) {
  return s->count;
}

// obtener el tamaño máximo de la pila
int stack_maxsize(stack* s) {
  return s->maxsize;
}

// Eliminar todos los elementos de la pila y liberar la memoria
void stack_destroy(stack* s){
    while(!stack_isempty(s)){
        pop(s);
    }
    stack_free(s);
}