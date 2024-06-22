#ifndef SIMPLE_LINKED_LIST_H
#define SIMPLE_LINKED_LIST_H

#include <stddef.h>

// Node structure definition
typedef struct _snode {
    char *val;
    struct _snode *next;
} SNode;

// Linked list structure definition
typedef struct _linked_list {
    SNode *begin;
    SNode *end;
    size_t size;
} LinkedList;

// Function declarations

// Create a new node with the given value
SNode *SNode_create(const char *val);

// Create a new linked list
LinkedList *LinkedList_create(void);

// Add a new node with the given value at the beginning of the list
void LinkedList_add_first(LinkedList *L, const char *val);

// Add a new node with the given value at the end of the list (inefficient version)
void LinkedList_add_last_slow(LinkedList *L, const char *val);

// Add a new node with the given value at the end of the list (efficient version)
void LinkedList_add_last(LinkedList *L, const char *val);

// Remove a node with the given value from the list
void LinkedList_remove(LinkedList *L, const char *val);

// Remove all nodes with the given value from the list
void LinkedList_remove_all(LinkedList *L, const char *val);

// Print the values of all nodes in the list
void LinkedList_print(const LinkedList *L);

// Get the size of the list
size_t LinkedList_size(LinkedList *L);

// Get the value of the first node in the list
char* LinkedList_first_val(LinkedList *L);

// Get the value of the last node in the list
char* LinkedList_last_val(LinkedList *L);

// Get the value of the node at the given index in the list
char* LinkedList_get_val(LinkedList *L, int index);

// Check if the list is empty and exit with an error if it is
void LinkedList_empty_check(LinkedList *L);

// Destroy the list and free all allocated memory
void LinkedList_destroy(LinkedList *L);

#endif // SIMPLE_LINKED_LIST_H
