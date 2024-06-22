#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _snode{
    char *val;
    struct _snode *next;
} SNode; // S de simples

typedef struct _linked_list{
    SNode *begin;
    SNode *end;
    size_t size;
} LinkedList;

SNode *SNode_create(const char *val) { // cria nó
    SNode *node = (SNode*) calloc(1, sizeof(SNode));
    node->val = strdup(val); // allocate and copy string
    node->next = NULL;
    return node;
}

LinkedList *LinkedList_create() { // cria lista, que tem ponteiro begin para o primeiro elemento da lista
    LinkedList *L = (LinkedList*) calloc(1, sizeof(LinkedList));
    L->begin = NULL;
    L->end = NULL;
    L->size = 0;
    return L;
}

void LinkedList_add_first(LinkedList *L, const char *val) { // insere nó no início da lista
    SNode *node = SNode_create(val); // nó que será inserido no início
    node->next = L->begin; // novo primeiro nó aponta para antigo primeiro nó, que agora será o segundo nó
    L->begin = node; // início da lista aponta para novo primeiro elemento
    L->size++;
    if (L->end == NULL) { // se end apontar para nulo, ou seja, se lista estava vazia
        L->end = node;
    }
}

void LinkedList_add_last_slow(LinkedList *L, const char *val) { // adiciona no final da lista
    SNode *node = SNode_create(val);
    if (L->begin == NULL) {
        L->begin = node;
        L->end = node;
    } else {
        SNode *aux_node = L->begin;
        while (aux_node->next != NULL) {
            aux_node = aux_node->next;
        }
        aux_node->next = node;
        L->end = node;
    }
    L->size++;
}

void LinkedList_add_last(LinkedList *L, const char *val) { // adiciona ao final de forma mais eficiente
    SNode *node = SNode_create(val);
    if (L->begin == NULL) {
        L->begin = node;
    } else {
        L->end->next = node;
    }
    L->end = node;
    L->size++;
}

void LinkedList_remove(LinkedList *L, const char *val) { // remove um nó com valor val
    if (L->begin != NULL) { // se lista não está vazia
        SNode *aux_node = L->begin;
        SNode *prev_aux_node = NULL;
        while (aux_node != NULL && strcmp(aux_node->val, val) != 0) { // enquanto não achou valor e não chegou ao final
            prev_aux_node = aux_node;
            aux_node = aux_node->next;
        }
        if (aux_node != NULL) { // se achou valor a ser removido
            if (L->end == aux_node) { // se o valor for o último
                L->end = prev_aux_node;
            }
            if (L->begin == aux_node) { // se o valor for o primeiro
                L->begin = L->begin->next;
            } else { // quando prev_aux_node não aponta para NULL, corrige encadeamento
                prev_aux_node->next = aux_node->next;
            }
            free(aux_node->val); // free the string
            free(aux_node); // free the node
            L->size--;
        }
    }
}

void LinkedList_remove_all(LinkedList *L, const char *val) {
    if (L->begin != NULL) { // se lista não está vazia
        SNode *aux_node = L->begin;
        SNode *prev_aux_node = NULL;
        SNode *removable_node = NULL;
        while (aux_node != NULL) {
            if (strcmp(aux_node->val, val) == 0) {
                if (L->end == aux_node) { // se o valor for o último
                    L->end = prev_aux_node;
                }
                if (L->begin == aux_node) { // se o valor for o primeiro
                    L->begin = L->begin->next;
                } else { // quando prev_aux_node não aponta para NULL, corrige encadeamento
                    prev_aux_node->next = aux_node->next;
                }
                removable_node = aux_node;
                aux_node = aux_node->next;
                free(removable_node->val); // free the string
                free(removable_node); // free the node
                L->size--;
            } else {
                prev_aux_node = aux_node;
                aux_node = aux_node->next;
            }
        }
    }
}

void LinkedList_print(const LinkedList *L) { // imprime lista
    SNode *aux_node = L->begin; // não aloca espaço para ponteiro auxiliar pq ele não precisa de um espaço para ele, o ponteiro vai apontar para outros espaços já alocados.
    printf("begin -> ");
    while (aux_node != NULL) { // último nó aponta para NULL
        printf("%s -> ", aux_node->val);
        aux_node = aux_node->next;
    }
    puts("NULL");
    if (L->end == NULL) {
        puts("L->end -> NULL");
    } else {
        printf("L->end -> %s\n", L->end->val);
    }
    printf("L->size = %ld\n\n", L->size);
}

size_t LinkedList_size(LinkedList *L) {
    return L->size;
}

char* LinkedList_first_val(LinkedList *L) {
    LinkedList_empty_check(L);
    return L->begin->val;
}

char* LinkedList_last_val(LinkedList *L) {
    LinkedList_empty_check(L);
    return L->end->val;
}

char* LinkedList_get_val(LinkedList *L, int index) {
    LinkedList_empty_check(L);
    if (index >= 0 || index < L->size) {
        SNode *aux_node = L->begin;
        for (int i = 0; i < index; i++) {
            aux_node = aux_node->next;
        }
        return aux_node->val;
    } else {
        fprintf(stderr, "INVALID INDEX\n");
        exit(EXIT_FAILURE);
    }
}

void LinkedList_empty_check(LinkedList *L) {
    if (L->begin == NULL) {
        fprintf(stderr, "ERROR! LIST IS EMPTY\n");
        exit(EXIT_FAILURE);
    }
}

void LinkedList_destroy(LinkedList *L) {
    SNode *aux_node = L->begin;
    SNode *removable_aux_node = NULL;
    while (aux_node != NULL) {
        removable_aux_node = aux_node;
        aux_node = aux_node->next;
        free(removable_aux_node->val); // free the string
        free(removable_aux_node); // free the node
    }
    free(L);
    L = NULL;
}
