#include <assert.h>
#include <string.h>
#include "BinarySearchTree.h"
#include "matam.h"

Tree treeCreate(int (*cpy)(Node, Data),void (*fre)(Data), double (*comp)(void*, void*), Data(*add)()){
    Tree newTree;
    newTree = ALLOC(struct Tree_s, 1);
    newTree->size = 0;
    newTree->root = NULL;
    newTree->cpy = cpy;
    newTree->fre = fre;
    newTree->comp = comp;
    newTree->add = add;
    return newTree;
}

int treeClear(Tree tree, Node root){
    if(!root){
        return 1;
    }
    treeClear(tree, root->left);
    treeClear(tree, root->right);
    tree->fre(tree);
    return 1;
}

Node appendNodeToTree(Tree tree, Node root, Data newData){
    Node newNode;
    if(!root){
        newNode = ALLOC(struct node ,1);
        newNode->data = newData;
        newNode->left = newNode->right = NULL;
        tree->size+=1;
        return newNode;
    }

    if(tree->comp(root->data, newData) == 0){
        return NULL;
    }
    if(tree->comp(root->data, newData)<0){
        root->left = appendNodeToTree(tree, root->left, newData);
    }
    else{
        root->right = appendNodeToTree(tree, root->right, newData);
    }
    return root;
}

int addNewNode(Tree tree){
    Data newData;
    newData = tree->add();
    appendNodeToTree(tree,tree->root,newData);
    return 1;
}

linkedList findNode(Tree tree, linkedList (*findFunc)(Tree)){
    return findFunc(tree);
}


double averageTree(Tree tree,Node node, double(*avgFunc)(Node)){
    double res;
    if (!tree){
        return 0;
    }
    res =(avgFunc(node))/tree->size;
    res += averageTree(tree,node->left,avgFunc);
    res += averageTree(tree,node->right,avgFunc);
    return res;
}


int addToArray(Node node, Data* arr, int idx){
    if(!node){
        return idx;
    }
    if(node->left){
        idx = addToArray(node->left, arr, idx);
    }
    idx+=1;
    arr[idx] = node->data;
    if(node->right){
        addToArray(node->right, arr, idx);
    }
    return idx;
}

Data* treeToArray(Tree tree){
    Data* dataArr = ALLOC(Data, tree->size);
    addToArray(tree->root, dataArr, 0);
    return dataArr;
}

void printTree(Node node, void (*printFunc)(Node)){
    if(!node) return;

    printTree(node->left,printFunc);
    printFunc(node);
    printTree(node->right,printFunc);
}

void freeNode(Tree tree, Node node){
    tree->fre(node->data);
    FREE(node);
}

void freeAllNodes(Tree tree, Node node){
    if (!node){
        return;
    }
    freeAllNodes(tree, node->left);
    freeAllNodes(tree, node->right);
    freeNode(tree, node);
}

void freeTree(Tree tree){
    freeAllNodes(tree, tree->root);
    FREE(tree);
}

Node deleteNode(Tree tree, Node node, Data deletedData){
    Node temp, follower, *followerAddr;

    if (!node) {
        return NULL;
    }

    /* searching wanted supplier in node's children*/
    if(tree->comp(node->data, deletedData) != 0) {
        /* Go left*/
        if(tree->comp(node->data, deletedData) < 0) {
            node->left = deleteNode(tree, node->left, deletedData);
        }
            /* Go right*/
        else {
            node->right = deleteNode(tree, node->right, deletedData);
        }

    }

    else {

/* Option 1: node is a leaf*/
        if (!(node->left) && !(node->right)) {
            freeNode(tree, node);
            tree->size--;
            return NULL;
        }
/* Option 2: node has only one child*/
        else if (!(node->left)) {
            temp = node->right;
            freeNode(tree, node);
            tree->size--;
            return temp;
        } else if (!(node->right)) {
            temp = node->left;
            freeNode(tree, node);
            tree->size--;
            return temp;
        }
/* Option 3: node has 2 children*/
        else {
            follower = node->right;
            followerAddr = &(node->right);
            while (follower->left) {
                followerAddr = &(follower->left);
                follower = follower->left;
            }
<<<<<<< HEAD
            freeNode(tree,node);
=======
            freeNode(tree, node);
>>>>>>> c16b1f1f490f4b478b73f56d4c351780ba82e13d
            tree->cpy(node, follower->data);
            *followerAddr = deleteNode(tree, follower, follower->data);
        }
    }
    return node;
}





