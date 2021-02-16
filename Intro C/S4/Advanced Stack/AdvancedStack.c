//
// Created by andru on 3/4/2020.
//

#include "AdvancedStack.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ADVANCED STACK

typedef struct node{
    struct node* next;
    int value;
} node_t;

typedef struct queue{
    struct node* tail;
    int size;
} queue_t  ;

/*
* Add @val value at the head of the @q queue
*
* @val     : the value to enqueue
* @q     : the queue
*
* @return 0 if no error, -1 otherwise
*
* pre : The queue q will always be valid, you don't need to handle the NULL case.
*/
int enqueue(queue_t* q, int val){
    struct node *temp_node = malloc(sizeof(struct node));
    if (temp_node == NULL) {
        return -1;
    }
    temp_node->value = val;
    temp_node->next = NULL;
    q->size++;
    if (q->tail == NULL) {
        q->tail = temp_node;
        temp_node->next = temp_node;
        return 0;
    } else if (q->tail == q->tail->next) {
        q->tail->next = temp_node;
        temp_node->next = q->tail;
        return 0;
    } else{
        struct node *head = q->tail->next;
        q->tail->next = temp_node;
        temp_node->next = head;
        return 0;
    }
}

/*
* Remove the node at the tail of the @q queue and return the value of this node
* @q         : the queue
* @return     : the value at the tail
*
* pre         : The given queue will always be valid, you do not need to handle the NULL case.
*/
int dequeue(queue_t* q){
    int return_value = q->tail->value;
    if (q->size == 1) {
        q->tail = NULL;
        q->size = 0;
        free(q->tail);
        return return_value;
    }

    q->size--;
    struct node *pretail_nodeptr = q->tail->next;

    int i = 0;
    while (q->tail != pretail_nodeptr->next) {
        i++;
        pretail_nodeptr = pretail_nodeptr->next;
    }

    pretail_nodeptr->next = q->tail->next;
    free(q->tail);
    q->tail = pretail_nodeptr;
    return return_value;
}

void print_AdvancedStatck(struct queue *q){
    printf(" Advanced Stack: \n");
    if (q->size == 0 && q->tail == NULL) {
        printf("la queue est vide");
        return;
    }
    struct node *currentnodeptr = q->tail->next;
    int i = 0;
    while (q->tail != currentnodeptr) {
        printf("%d: %d\n", i, currentnodeptr->value);
        i++;
        currentnodeptr = currentnodeptr->next;
    }
    printf("%d: %d\n", i, q->tail->value);
    printf("null\n\n");
}

void print_dequeue(struct queue *q){
    printf("The removed value is %d\n",dequeue(q));
}


int main_AdvancedStack(){
    printf("Main de Advanced Stack:\n\n");
    struct queue *q = malloc(sizeof(struct queue));
    q->tail = NULL;
    q->size = 0;

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    print_AdvancedStatck(q);

    print_dequeue(q);
    print_AdvancedStatck(q);

    print_dequeue(q);
    print_dequeue(q);
    print_AdvancedStatck(q);

    print_dequeue(q);
    print_dequeue(q);
    print_AdvancedStatck(q);
    return 0;
}