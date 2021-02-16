//
// Created by andru on 2/29/2020.
//

#include "SImpleLinkedList.h"

//
// Created by andru on 2/29/2020.
//
#include <stdio.h>
#include <stdlib.h>

/**
* Structure node
*
* @next: pointer to the next node in the list, NULL if last node_t
* @value: value stored in the node
*/
typedef struct node {
    struct node *next;
    int value;
} node_t;

/**
* Structure list
*
* @first: first node of the list, NULL if list is empty
* @size: number of nodes in the list
*/
typedef struct list {
    struct node *first;
    int size;
} list_t;

/*
* Create a new node containing the value @value.
*
* @value: value stored in the node
* @next : pointer to next node, initialised to NULL.
* @return: returns the pointer to the newly created node, or NULL if an error occurred.
*/
node_t *init_node(int value) {
    node_t *newnodeptr = malloc(sizeof(node_t));
    if (newnodeptr == NULL) {
        return NULL;
    }
    newnodeptr->next = NULL; // or (*newnodeptr).next = NULL
    newnodeptr->value = value;
    return newnodeptr;
}

/*
* Add a node at the head of the list @list and increment the number of nodes in the list (member `size`)
*
* @l: linked list
* @value: value to add to the list
*
* @return: 0 if success, 1 otherwise
*/
int add_node(list_t *list, int value) {
    if (list == NULL) {
        return 1;
    }
    struct node *newnode = init_node(value);
    if (newnode == NULL) {
        return 1;
    }
    newnode->next = list->first;
    list->first = newnode;
    list->size++;
    return 0;
}

void print_LL(list_t *list){
    printf("Linkedlist of size %d:\n", list->size);
    struct node *actualnode = list->first;
    int i = 0;
    while (actualnode != NULL) {
        printf("%d: %d\n", i, actualnode->value);
        i++;
        actualnode = actualnode->next;
    }
    printf("null\n");
}

int main_LinkedList(){
    printf("Main LinkedList: \n\n");
    struct list *l = malloc(sizeof(struct list));
    l->first = NULL;
    l->size = 0;
    add_node(l, 11);
    add_node(l, 1);
    add_node(l, 2);
    add_node(l, 3);
    print_LL(l);
}