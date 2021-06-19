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

void freeList(linkedList list);
void printTree(Node node, void (*printFunc)(Data));
int addNewNode(Tree tree);
Tree treeCreate(int (*cpy)(Node, Data),void (*fre)(Data), double (*comp)(void*, void*), Data (*add)());
void freeTree(Tree tree);
Node appendNodeToTree(Tree tree, Node root, Data newData);
Node deleteNode(Tree tree, Node node, void* deletedData, double (*comp)(Data, void*));
int findNode(Node node, Data findBy, linkedList list, nodeList* head);
double averageTree(Tree tree,Node node,double(*avgParam)(Node));
void freeNode(Tree tree, Node node);
void freeAllNodes(Tree tree, Node node);
Data* treeToArray(Tree tree);
void printArray(Data* arr, void (*printFunc)(Data),int size);






#endif
