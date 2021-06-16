#include <string.h>
#include "GenericDataStructures.h"
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
    tree->root = appendNodeToTree(tree,tree->root,newData);
    return 1;
}


double averageTree(Tree tree,Node node, double(*avgParam)(Node)){
    double res;
    if (!node){
        return 0;
    }
    res = (avgParam(node)) / tree->size;
    res += averageTree(tree, node->left, avgParam);
    res += averageTree(tree, node->right, avgParam);
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
            freeNode(tree, node);
            tree->cpy(node, follower->data);
            *followerAddr = deleteNode(tree, follower, follower->data);
        }
    }
    return node;
}

/*-----------------------Linked List Functions----------------------*/

linkedList listCreate(double (*comp)(void*, void*), void (*fre)(Data)) {

    linkedList new_list = ALLOC(struct linkedList, 1);
    new_list->head = NULL;
    new_list->comp = comp;
    new_list->fre = fre;
    return new_list;
}

void freeListNode(linkedList list, nodeList node){
    list->fre(node->data);
    FREE(node);
}

void freeListNodes(linkedList list, nodeList node){
    nodeList nextOne;
    if (!node){
        return;
    }
    nextOne = node->next;
    freeListNode(list, node);
    freeListNodes(list, nextOne);
}

void freeList(linkedList list){
    freeListNodes(list, list->head);
    FREE(list);
}

nodeList createNode_l(Data data){
    nodeList new = ALLOC(struct nodeList,1);
    new->next = NULL;
    new->data = data;
    return new;
}

/*insert a node in linked list.*/
int insertNewNode(nodeList * head, Data data, double (*comp)(void*, void*)){
    nodeList newNode = NULL, curr;

    /*initializing new node. */
    newNode = createNode_l(data);

    /*true when list is empty, or new node's data parameter is smaller then first node's*/
    if ((*head == NULL) || comp((*head)->data, data) >= 0) {
        newNode->next = *head;
        *head = newNode;
        return 1;
    }

    /*finds the first bigger node data*/
    curr = *head;
    while ((curr->next) && comp(curr->next->data,newNode->data) < 0) {
        curr = curr->next;
    }

    /*inserting the new node after the current one.*/
    newNode->next = curr->next;
    curr->next = newNode;
    return 1;
}

/*linked list has created outside of the function*/
int findNode(Node node, Data findBy, linkedList list, nodeList* head){
    if(!node){
        return 0;
    }
    findNode(node->left, findBy, list, head);

    if(list->comp(node->data, findBy) == 0) {
        insertNewNode(head, node->data, list->comp);
    }
    findNode(node->right, findBy, list, head);

    return 1;
}







