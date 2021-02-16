//
// Created by andru on 3/3/2020.
//

#include "OrderedLinkedList.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct node{
    char val;
    struct node *next;
} node_t;

/*
* @return: 0 if equals, negative number if @b is greater,
* and positive number otherwise
*/
int compare(char a, char b) {
    return a - b;
}

/*
* @value: value to be inserted. If the value is already in the list, no element is added and the list is not modified
* @fun: comparison function which defines the order relationship of the list
* @head: first node of the list, head != NULL
* @return: 0 if success, -1 otherwise
*/
int insert(node_t **head, char val, int (*cmp)(char,char)) {
    if (*head == NULL) {
        node_t *listptr = malloc(sizeof(node_t));
        if (listptr == NULL) {
            return -1;
        }
        listptr->val = val;
        listptr->next = NULL;
        *head = listptr;
        return 0;
    }
    if ((cmp)((*head)->val, val) == 0){
        return 0;
    }

    if ((cmp)((*head)->val, val) > 0) {
        struct node * tempo_node = malloc(sizeof(node_t));
        if (tempo_node == NULL) {
            return -1;
        }
        tempo_node->val = val;
        tempo_node->next = *head;
        *head = tempo_node;
        return 0;
    }

    node_t *prenodeptr = *head;
    node_t *postnodeptr = (*head)->next;
    while (postnodeptr != NULL){
        if ((cmp)(postnodeptr->val, val) > 0) {    //Insert dedans
            struct node *tempo_node = malloc(sizeof(node_t));
            if (tempo_node == NULL) {
                return -1;
            }
            tempo_node->val = val;
            prenodeptr->next = tempo_node;
            tempo_node->next = postnodeptr;
            return 0;
        } else if ((cmp)(postnodeptr->val, val) == 0){    //Deja présent -> change rien
            return 0;
        }else{
            prenodeptr = prenodeptr->next;
            postnodeptr = postnodeptr->next;
        }
    }
    //Rajoute a la fin
    struct node * tempo_node = malloc(sizeof(node_t));
    if (tempo_node == NULL) {
        return -1;
    }
    tempo_node->val = val;
    tempo_node->next = NULL;
    prenodeptr->next = tempo_node;
    return 0;
}


void printLL(node_t **head){
    printf("Linkedlist :\n");
    struct node *n = *head;
    int i = 0;
    while (n != NULL) {
        printf("%d:  %c\n", i, n->val);
        i++;
        n = n->next;
    }
    printf("null\n");
}

int main2(){
    node_t *listptr = NULL;
    node_t **headptr2 = &listptr;
    int (*compareptr) (char, char) = &compare;
    insert(headptr2, '3', compareptr);
    insert(headptr2, '3', compareptr);
    insert(headptr2, '2', compareptr);
    insert(headptr2, '7', compareptr);
    insert(headptr2, 'a', compareptr);
    insert(headptr2, 'c', compareptr);
    insert(headptr2, 'b', compareptr);
    insert(headptr2, 't', compareptr);
    insert(headptr2, '1', compareptr);
    insert(headptr2, '0', compareptr);
    printLL(headptr2);
    return 0;
}


int main_OrderedLL(){
    printf("Main de Ordered LinkedList:\n");
    //Initialisation
    node_t *listptr = malloc(sizeof(node_t));
    listptr->val = '0';
    listptr->next = NULL;
    node_t **headptr2 = &listptr;
    int (*compareptr) (char, char) = &compare;
    //Fill the OLL
    insert(headptr2, '3', compareptr);
    insert(headptr2, '3', compareptr);
    insert(headptr2, '2', compareptr);
    insert(headptr2, '7', compareptr);
    insert(headptr2, 'a', compareptr);
    insert(headptr2, 'c', compareptr);
    insert(headptr2, 'b', compareptr);
    insert(headptr2, 't', compareptr);
    insert(headptr2, '1', compareptr);
    insert(headptr2, '0', compareptr);
    printLL(headptr2);

    main2();
    return 0;
}