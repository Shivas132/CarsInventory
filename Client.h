#ifndef CLIENT_H
#define CLIENT_H
#include "GenericDataStructures.h"

typedef struct{

    char* name;
    char* surname;
    double id;
    double rentedCarLicense;
    char rentDate[11];
    char rentHour[6];
    double priceForDay;
}Client;

typedef struct clientNode_t{
    Client client;
    struct clientNode_t* left;
    struct clientNode_t* right;
}clientNode;

typedef struct {
    clientNode* root;
    int size;
} clientBST;

typedef struct clientNode_l{
    Client client;
    struct clientNode_l* next;
}clientNode_l;

typedef struct clientList{
    clientNode_l* head;
}clientList;


/*creates empty clientNode*/
Tree createClientTree();

/*adds new client to the client to clientTree. return 1 if succeed, 0 if failed*/
int addNewClient(Tree tree);

/*help function to call in addNewClient*/
clientNode * appendClientToTree(clientNode * tree, Client newClient,clientBST* clientBst);


/*gets id number of a client and delete it from the list. returns the tree's root.*/
int deleteClient(Tree tree);

/*deletes all the clients from the tree. returns 1.*/
int deleteAllClients(Tree tree);

void printClientCarsForGivenRentDate(clientNode * tree);

int clearClientsList(clientList* list);

linkedList findClient(Node root);

void printClientList(nodeList node);

#endif
