#ifndef GDS_H
#define GDS_H

typedef struct Tree_s* Tree;
typedef void* Data;
typedef struct node* Node;
typedef struct nodeList* nodeList;
typedef struct linkedList* linkedList;

struct nodeList{
    Data data;
    nodeList next;
};

struct linkedList{
    nodeList head;
    double (*comp)(void*, void*);
    void (*fre)(Data);
    };

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
void freeTree(Tree tree);
Node appendNodeToTree(Tree tree, Node root, Data newData);
Node deleteNode(Tree tree, Node node, void* deletedData);
int findNode(Tree tree, Node node, Data findBy, linkedList list, nodeList* head);
double averageTree(Tree tree,Node node,double(*avgFunc)(Node));
void freeNode(Tree tree, Node node);
void freeAllNodes(Tree tree, Node node);
void printTree(Node node, void (*printFunc)(Node));





#endif
