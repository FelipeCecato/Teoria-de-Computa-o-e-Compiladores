#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó
typedef struct Node {
    char *data;
    struct Node *next;
} Node;

// Definição da estrutura da lista
typedef struct LinkedList {
    Node *head;
} LinkedList;

// Função para inicializar a lista
void initializeList(LinkedList *list) {
    list->head = NULL;
}

// Função para criar um novo nó
Node* createNode(const char *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Erro ao alocar memória para novo nó.\n");
        exit(1);
    }
    newNode->data = strdup(data);
    newNode->next = NULL;
    return newNode;
}

// Função para inserir um novo elemento na lista
void insertElement(LinkedList *list, const char *data) {
    if (containsElement(list, data)) {
        return;
    }
    Node *newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
}

// Função para remover um elemento da lista
void removeElement(LinkedList *list, const char *data) {
    Node *current = list->head;
    Node *previous = NULL;
    while (current != NULL && strcmp(current->data, data) != 0) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        fprintf(stderr, "Elemento não encontrado na lista.\n");
        return;
    }
    if (previous == NULL) {
        list->head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current->data);
    free(current);
}

// Função para verificar se um elemento está na lista
int containsElement(LinkedList *list, const char *data) {
    Node *current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return 1; // Elemento encontrado
        }
        current = current->next;
    }
    return 0; // Elemento não encontrado
}

// Função para remover todos os elementos da lista
void removeAllElements(LinkedList *list) {
    Node *current = list->head;
    Node *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current->data);
        free(current);
        current = nextNode;
    }
    list->head = NULL;
}

// Função para imprimir a lista
void printList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
