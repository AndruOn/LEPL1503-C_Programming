//
// Created by andru on 3/3/2020.
//

#include "FIlteringLL.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Hint : You should use memcpy(3) for this question
*/

struct node {
    struct node *next;
    int hash;
    int id;
    char name[20];
    char buffer[100];
    unsigned int timestamp;
    char acl;
    short flow;
    char *parent;
    void *fifo;
};

void print_LL(struct node *head){
    printf("Linkedlist :\n");
    struct node *n = head;
    int i = 0;
    while (n != NULL) {
        printf("%d:  %s\n", i, n->parent);
        i++;
        n = n->next;
    }
    printf("null\n");
}


/* pair_filter
 * Make a copy of the linked list starting at head,
 * only taking the elements with an even index
 *
 * @head : head of a linked list, possibly NULL
 * @return: pointer to the filtered linked list, return NULL if error or if head == NULL
 */
struct node *pair_filter(struct node *head) {
    if (head == NULL) {
        return NULL;
    }

    int i = 1;
    size_t sizenode = sizeof(struct node);
    struct node *newlist; //pointeur vers début de la liste a return
    struct node *newnode; //parcours la liste de return pour rajouter les nodes

    newnode = malloc(sizenode);
    if (newnode == NULL) {
        return NULL;
    }
    memcpy(newnode, head, sizenode);
    newlist = newnode;

    struct node *ptrnode = head->next; //avance dans la liste argument
    while (ptrnode != NULL) {
        if (i % 2 == 0) {
            struct node * tempo_node = malloc(sizenode);
            if (tempo_node == NULL) {
                return NULL;
            }
            memcpy(tempo_node, ptrnode, sizenode);
            newnode->next = tempo_node;
            newnode = newnode->next;
        }
        ptrnode = ptrnode->next;
        i++;
    }
    newnode->next = NULL;
    return newlist;
}


void* pushLL(struct node **head,char* name) {
    struct node *newnodeptr = malloc(sizeof(struct node));
    if (newnodeptr == NULL) {
        return NULL;
    }
    newnodeptr->next = *head;
    newnodeptr->parent = name;
    *head = newnodeptr;
    return NULL;
}

struct node* initList(char* name){
    struct node *head = malloc(sizeof(struct node));
    head->parent = name;
    head->next = NULL;
    return head;
}



void print_LL_tropexhaustif(struct node *head){
    printf("Linkedlist :\n");
    struct node *n = head;
    int i = 0;
    while (n != NULL) {
        printf("%d: hash:%d id:%d name:%s buffer:%s timestamp:%d acl:%c flow:%d parent:%s \n",
                i, n->hash, n->id, n->name, n->buffer, n->timestamp, n->acl, n->flow, n->parent);
        i++;
        n = n->next;
    }
    printf("null\n");
}



int main_FilteringLL(){
    struct node* head = initList("dernier");
    struct node** listptr = &head;
    pushLL(listptr, "5");
    pushLL(listptr, "4");
    pushLL(listptr, "3");
    pushLL(listptr, "2");
    pushLL(listptr, "1");
    pushLL(listptr, "0");
    print_LL(*listptr);
    printf("\nAPRES FILTER:\n\n");
    print_LL(pair_filter(*listptr));
    return 0;
}

