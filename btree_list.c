/*
Desarrollar una función, y todas las funciones auxiliares necesarias, que tome un árbol binario como
entrada y genere una lista enlazada dinámica que contenga sublistas (también enlazadas dinámicamente). Cada
nodo de la lista representará un nivel del árbol, y la sublista correspondiente contendrá los nodos de ese
nivel. Cada nodo de la sublista contendrá la clave y un puntero al nodo respectivo en el árbol original. Las sublistas
deben estar ordenadas por clave.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct _btn{
    int key;
    struct _btn* left;
    struct _btn* right;
} btn;

// Estructura para la lista enlazada dinámica que contendrá 
// - las sublistas de nodos de cada nivel
// - los niveles del árbol
// Es la misma estructura para nodos y subnodos. 
typedef struct _node {
    int key;
    void* data; // Puntero a árbol o a sublista. 
    struct _node* next;
} node;

node* node_new (int key, void* data) {
    node* n = malloc(sizeof(node));
    if (n != NULL) {
        n->key = key;
        n->data = data;
        n->next = NULL;
    }
    return n;
}

node* insert_sorted(node** head, node* new_node) {
    while (*head != NULL && (*head)->key < new_node->key) {
        head = &((*head)->next);
    }
    new_node->next = *head;
    *head = new_node;
}

node* gen_list (btn* root){
    node* head = NULL;
    node** tail = &head; // Puntero al puntero de la cabeza para insertar al final
    queue* q = queue_new(100); // Crear una cola para el recorrido por niveles
    enqueue(q, root); // Encolar la raíz del árbol
    int level = 0; // Nivel actual del árbol
    
    while (!queue_isempty(q)) {
        int level_size = queue_length(q); // Tamaño del nivel actual
        node* sublist_head = NULL; // Cabeza de la sublista para el nivel actual
        node* sublist_tail = NULL; // Cola de la sublista para el nivel actual
        *tail = node_new(level, NULL); // Crear un nuevo nodo para la lista principal        

        for (int i = 0; i < level_size; i++) {
            btn* current = (btn*)dequeue(q); // Desencolar el nodo actual
            insert_sorted(&(*tail)->data, node_new(current->key, current));
            if (current->left != NULL) {
                enqueue(q, current->left); // Encolar el hijo izquierdo
            }
            if (current->right != NULL) {
                enqueue(q, current->right); // Encolar el hijo derecho
            }
        }
        tail = &((*tail)->next); // Actualizar el puntero de la cola

    }

    queue_free(q); // Liberar la cola

    return head;
}