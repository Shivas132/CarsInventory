#ifndef BTS_H
#define BTS_H

typedef struct Tree_s* Tree;
typedef void* Data;
typedef struct node* Node;
typedef struct nodeList* nodeList;


struct nodeList{
    Data data;
    nodeList next;
};

typedef struct linkedList{
    nodeList head;
    }linkedList;

struct node {
    Data data;
    Node left;
    Node right;
};

struct Tree_s{
    Node root;
    int size;
    int(*cpy)(Node, Data);
    void (*fre)(Data);
    double (*comp)(void*, void*);
    Data (*add)();
};

int addNewNode(Tree tree);
Tree treeCreate(int (*cpy)(Node, Data),void (*fre)(Data), double (*comp)(void*, void*), Data (*add)());
int treeClear(Tree tree, Node root);
Node appendNodeToTree(Tree tree, Node root, Data newData);
Node deleteNode(Tree tree, Node node, void* deletedData);
linkedList findNode(Tree tree, linkedList (*findFunc)(Tree));
double averageTree(Tree tree,Node node,double(*avgFunc)(Node));
void freeNode(Tree tree, Node node);





#endif
