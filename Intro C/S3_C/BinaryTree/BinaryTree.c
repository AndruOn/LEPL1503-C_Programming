//
// Created by andru on 2/29/2020.
//

#include "BinaryTree.h"



/*
* Node has a value, @value, and two children, @left and @right.
* All the children of @left and itself have a smaller value than the node and all the children of @right and itself have a larger value than node
*/
#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int value;
    struct node* left; // to smaller values
    struct node* right; // to larger values
} node_t;
typedef struct bt{
    struct node* root;
} bt_t;

/*
* Return 1 if there is a node containing @value in @tree and 0 otherwise.
*/
int containsPasRecursif(bt_t* tree, int value) {
    if (tree == NULL) {
        return 0;
    }
    node_t* node = tree->root; // ou node_t* node = (*tree).root;
    while (node != NULL) {
        if (node->value == value) {return 1;}
        else if (node->value > value) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return 0;
}

int contains(bt_t* tree, int value) {
    if (tree == NULL || tree->root == NULL) {
        return 0;
    }
    node_t* node = tree->root; // ou node_t* node = (*tree).root;
    int nvalue = node->value;
    struct bt b;
    if (value == nvalue) {
        return 1;
    } else if (value > nvalue) {
        b.root = node->right;
        return contains(&b, value);
    } else {
        b.root = node->left;
        return contains(&b, value);
    }
}

int main_BinaryTree(){
    return 0;
}

