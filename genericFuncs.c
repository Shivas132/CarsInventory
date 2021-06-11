#include "genericFucncs.h"
#include "matam.h"


Tree treeCreate(Data (cpy)(Data),void (fre)(Data), int (comp)(void*, void*), Data (add)()){
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
        newNode->data = tree->cpy(newData);
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

int treeRemove(Tree tree, Node root, void* parameter){
    Node temp, *follower, **followerAddr;
}

double averageTree(Tree tree, double(*avgFunc)(Node, int)){
    return avgFunc(tree->root, tree->size);
}
