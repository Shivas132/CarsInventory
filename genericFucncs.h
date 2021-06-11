#ifndef GENERICFUCNCS_H
#define GENERICFUCNCS_H




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
    Data (*cpy)(Data);
    void (*fre)(Data);
    int (*comp)(void*, void*);
    Data (*add)();
};

int addNewNode(Tree tree);
Tree treeCreate(Data (cpy)(Data),void (fre)(Data), int (comp)(void*, void*), Data (add)());
int treeClear(Tree tree, Node root);
Node appendNodeToTree(Tree tree, Node root, Data newData);
int treeRemove(Tree tree, Node root, void* parameter);
linkedList findNode(Tree tree, linkedList (*findFunc)(Tree));





#endif
