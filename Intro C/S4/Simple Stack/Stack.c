//
// Created by andru on 2/29/2020.
//
#include "Stack.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Hints :

    char *name is also a pointer, memory must be allocated by using malloc(3) to copy the string on the stack.
    Other useful commands: strncpy(3) and strlen(3).
    Do not forget to free all the allocated space when popping one element.
*/

struct node {
    struct node *next;
    char *name;
};


/**
* Remove the top element of the stack and return its content.
*
* @head : pointer to the top of the stack
* @result : pointer to store the popped element
*
* @return 0 if no error, 1 otherwise
*
* pre : @result contains a null-terminated correct string
* post : @result contains the string @name from the element at the top of the stack
*/

int pop(struct node **head, char *result){
    struct node *first = *head;
    strcpy(result, first->name);
    *head = (*head)->next;
    printf("%s\n",first->name);
    free(first);
    return 0;
}

/**
* Add @name at the "top" of the stack.
*
* @head : pointer to the top of the stack
* @name : the string to be placed in the element at the top of the stack
*
* @return 0 if no error, 1 otherwise
*/

int push(struct node **head, const char *value){
    struct node *newnode = malloc(sizeof(struct node));
    if (newnode == NULL) {
        return 1;
    }
    newnode->name = (char*) value;
    newnode->next = *head;
    *head = newnode;
    return 0;
}

void print_Stack(struct node *head){
    printf("Stack: \n");
    struct node *node = head;
    int i = 0;
    while (node != NULL) {
        printf("%d: %s\n", i, node->name);
        i++;
        node = node->next;
    }
    printf("null\n\n");
}

void print_popval(struct node **head){
    char* name = malloc(sizeof(char) * 20);
    if (name == NULL) {
        printf("malloc a beugé");
    }
    pop(head, name);
    printf("the name of the poped node: %s\n",name);
    free(name);
}

int main_SimpleStack(){
    printf("Main Simple Stack:\n");
    struct node* stack = malloc(sizeof(struct node));
    stack->next = NULL;
    stack->name = "last";

    push(&stack, "2");
    push(&stack, "1");
    push(&stack, "0");
    print_Stack(stack);

    print_popval(&stack);
    print_popval(&stack);
    print_Stack(stack);

    push(&stack, "ca marche");
    print_Stack(stack);
    return 0;
}

