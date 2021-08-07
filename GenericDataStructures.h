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

/*creates new Binary search tree.*/
Tree treeCreate(int (*cpy)(Node, Data),void (*fre)(Data), double (*comp)(void*, void*), Data (*add)());

/*gets data from user by add function, and gives it to appendNodeToTree() which adding it to the tree inorder*/
int addNewNode(Tree tree);

/*deletes node from the tree. gets comparing function to delete by.*/
Node deleteNode(Tree tree, Node node, void* deletedData, double (*comp)(Data, void*));

/*free all nodes of a tree recursively*/
void freeAllNodes(Tree tree, Node node);

/*free all tree's allocated memory*/
void freeTree(Tree tree);

/*gets printing format function and calls it recursively on the tree.*/
void printTree(Node node, void (*printFunc)(Data));

/*gets parameter to sum and average by avgParam function, return the average of it.*/
double averageTree(Tree tree,Node node,double(*avgParam)(Node));

/*creates sorted array of pointers to tree's nodes data*/
Data* treeToArray(Tree tree);

/*gets printing format function and calls it for every object in the array.*/
void printArray(Data* arr, void (*printFunc)(Data),int size);

/*free all allocating for linked list every node in linked list*/
void freeList(linkedList list);

/*finding node in tree by unknown parameter
 * linked list has created outside of this function*/
int findNode(Node node, Data findBy, linkedList list, nodeList* head);




#endif
