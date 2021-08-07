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


/*using generic function treeCreate to initialize new clients tree.*/
Tree createClientTree();

/*using generic function addNewNode to add new client to the clients tree*/
int addNewClient(Tree tree);

/*using generic function deleteNode to remove client node from the tree.*/
void deleteClient(Tree tree);

/*using generic function deleteAllNodes to remove all clients from the tree and free all allocating memory.*/
int deleteAllClients(Tree tree);

/*gets rent date from user, prints name and surname of clients that rented a car in this date.*/
void printClientCarsForGivenRentDate(Node node);

/*gets searching parameter, and input from user.
 * returns linked list struct with all founded clients */
linkedList findClient(Node root);

/*prints all clients names in linked list*/
void printClientList(nodeList node);

/*print all the fields of given client*/
void printClientData(Data data);

#endif
