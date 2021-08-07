#include <string.h>
#include "GenericDataStructures.h"
#include "matam.h"

/*creates new Binary search tree. gets methods for specific data structs.
 * param cpy: copy function.
 * param fre: free allocated memory function
 * param comp: comparing function.
 * param add: gets input from user for data's firelds.*/
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

/*adding new node inorder.*/
Node appendNodeToTree(Tree tree, Node root, Data newData){
    Node newNode;
    if(!root){
        /*create new node with given data.*/
        newNode = ALLOC(struct node ,1);
        newNode->data = newData;
        newNode->left = newNode->right = NULL;
        tree->size+=1;
        return newNode;
    }

    /*preventing doubles of nodes in the tree.*/
    if(tree->comp(root->data, newData) == 0){
        return root;
    }
    /*finds which direction to go down the tree.*/
    if(tree->comp(root->data, newData)>0){
        root->left = appendNodeToTree(tree, root->left, newData);
    }
    else{
        root->right = appendNodeToTree(tree, root->right, newData);
    }
    return root;
}

/*gets data from user by add function, and gives it to appendNodeToTree()*/
int addNewNode(Tree tree){
    Data newData;
    newData = tree->add();
    tree->root = appendNodeToTree(tree,tree->root,newData);
    return 1;
}

/*gets parameter to sum and average by avgParam function, return the average of it.*/
double averageTree(Tree tree,Node node, double(*avgParam)(Node)){
    double res;
    if (!node){
        return 0;
    }
    res = (avgParam(node)) / tree->size; /*current node value*/
    res += averageTree(tree, node->left, avgParam); /*left side value*/
    res += averageTree(tree, node->right, avgParam); /*right side value*/
    return res;
}

/*adds tree nodes data to an array of pointers, sorted.
 * idx param always starts as 0.*/
int addToArray(Node node, Data* arr, int idx){
    if(node==NULL){
        return idx;
    }

    /*finds the most left node and begins adding from it.*/
    if(node->left){
        idx = addToArray(node->left, arr, idx);
    }
    arr[idx] = node->data; /*adds current nodes and increase idx*/
    idx+=1;

    /*adds right side*/
    if(node->right){
        addToArray(node->right, arr, idx);
    }
    return idx;
}

/*creates sorted array of pointers to tree's nodes data*/
Data* treeToArray(Tree tree){
    Data* dataArr = ALLOC(Data, tree->size);
    addToArray(tree->root, dataArr, 0);
    return dataArr;
}

/*gets printing format function and calls it for every object in the array.*/
void printArray(Data* arr, void (*printFunc)(Data),int size){
    int i;
    for (i=0;i<size;i++){
        printFunc(arr[i]);
    }
}

/*gets printing format function and calls it recursively on the tree.*/
void printTree(Node node, void (*printFunc)(Data)){
    if(!node){
        return;
    }

    printTree(node->left,printFunc);
    printFunc(node->data);
    printTree(node->right,printFunc);
}

/*free node's all allocated memory*/
void freeNode(Tree tree, Node node){
    tree->fre(node->data);
    FREE(node->data);
    FREE(node);
    }

/*free all nodes of a tree recursively*/
void freeAllNodes(Tree tree, Node node){
    if (!node){
        return;
    }
    freeAllNodes(tree, node->left);
    freeAllNodes(tree, node->right);
    freeNode(tree, node);
}

/*free all tree's allocated memory*/
void freeTree(Tree tree){
    freeAllNodes(tree, tree->root);
    FREE(tree);
}

/*deletes node from the tree. gets comparing function to delete by.*/
Node deleteNode(Tree tree, Node node, Data deletedData, double (*comp)(Data, void*)){
    Node temp, follower, *followerAddr;
    if (!node) {
        return NULL;
    }

    /* searching wanted node in node's children*
     * compares by comp param.*/
    if(comp(node->data, deletedData) != 0) {
        /* Go left*/
        if(comp(node->data, deletedData) > 0) {
            node->left = deleteNode(tree, node->left, deletedData, comp);
        }
            /* Go right*/
        else {
            node->right = deleteNode(tree, node->right, deletedData, comp);
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
            tree->fre(node->data);
            tree->cpy(node, follower->data);
            /*in next call, compare will be by tree's comparing function*/
            *followerAddr = deleteNode(tree, follower, follower->data, tree->comp);
        }
    }
    return node;
}

/*-----------------------Linked List Functions----------------------*/

/*recursive function free every node in linked list*/
void freeListNodes(linkedList list, nodeList node){
    nodeList nextOne;
    if (!node){
        return;
    }
    nextOne = node->next;
    FREE(node);
    freeListNodes(list, nextOne);
}

/*free all allocating for linked list every node in linked list*/
void freeList(linkedList list){
    freeListNodes(list, list->head);
    FREE(list);
}

/*creating new node for the linked list*/
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

/*finding node in tree by unknown parameter
 * linked list has created outside of this function*/
int findNode(Node node, Data findBy, linkedList list, nodeList* head){
    int res=0;
    if(!node){
        return 0;
    }
    res += findNode(node->left, findBy, list, head);

    if(list->comp(node->data, findBy) == 0) {
        insertNewNode(head, node->data, list->comp);
        res++;
    }
    res+= findNode(node->right, findBy, list, head);
    return res;
}







