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


/*creates empty clientNode*/
Tree createClientTree();

/*adds new client to the client to clientTree. return 1 if succeed, 0 if failed*/
int addNewClient(Tree tree);

/*gets licenseNum number of a client and delete it from the list. returns the tree's root.*/
void deleteClient(Tree tree);

/*deletes all the clients from the tree. returns 1.*/
int deleteAllClients(Tree tree);

void printClientCarsForGivenRentDate(Node node);

void printClientData(Data data);

linkedList findClient(Node root);

void printClientList(nodeList node);



#endif
