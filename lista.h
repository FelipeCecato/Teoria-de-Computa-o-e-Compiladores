#ifndef LISTA_H
#define LISTA_H

// Definição da estrutura do nó
typedef struct Node {
    char *data;
    struct Node *next;
} Node;

// Definição da estrutura da lista
typedef struct LinkedList {
    Node *head;
} LinkedList;

void initializeList(LinkedList *list);
Node* createNode(const char *data);
void insertElement(LinkedList *list, const char *data);
void removeElement(LinkedList *list, const char *data);
int containsElement(LinkedList *list, const char *data);
void removeAllElements(LinkedList *list);
void printList(LinkedList *list);

#endif