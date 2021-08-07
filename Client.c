#include <string.h>
#include <stdio.h>
#include "FillField.h"
#include "Client.h"


/*generate new client and getting all the information from the user
 *returns pointer to the new client as Data (void*)*/
Data setClientData(){
    Client* newClient;
    double id;
    double rentedCarLicense;
    char rentDate[11];
    char rentHour[6];
    double priceForDay;
    newClient = ALLOC(Client, 1);
    printf("please enter new client's details: \n");

    /*setting user inputs to fields
     *checking input validation*/
    puts("please enter client name: ");
    newClient->name = fillFiledStrDynamic(2);

    puts("please enter client surname: ");
    newClient->surname = fillFiledStrDynamic(2);

    puts("please enter client's ID (9 digits): ");
    fillFieldDouble(&id, 9, 1);
    newClient->id = id;

    puts("please enter rented car license (7 digits): ");
    fillFieldDouble(&rentedCarLicense, 7, 1);
    newClient->rentedCarLicense = rentedCarLicense;

    puts("please enter renting date (from 2000) (dd/mm/yyyy format only): ");
    fillFieldStr(rentDate, 10, 3,1);
    strcpy(newClient->rentDate, rentDate);

    puts("please enter renting hour: (mm:hh format only) ");
    fillFieldStr(rentHour, 5, 4, 1);
    strcpy(newClient->rentHour, rentHour);

    puts("please enter price per day: (max 3 digits) ");
    fillFieldDouble(&priceForDay,3, 0);
    newClient->priceForDay = priceForDay;

    return newClient;
}
/*---------------------comparing functions---------------------*/

/*comparing between Client and Date*/
double dateCompare(Data client, Data date){
    return strcmp(((Client*)(client))->rentDate, (char*)date);
}

/*comparing between client(Data) and id(Double) */
double clientsIdCompare(Data client, void* id){
    return ((Client*)(client))->id - (*(double*)id);
}

/*comparing between two clients(Data)*/
double clientCompare(Data client1, Data client2){
    return ((Client *)client1)->id-((Client *)client2)->id;
}


/*copying data to destination node.
 * allocating new memory for dynamic allocated data copying.*/
int clientCopy(Node dest, Data source){
    Client* clientData = ((Client*)dest->data);
    Client* clientSource = ((Client*)source);

    clientData->name = copyField(clientSource->name);
    clientData->surname = copyField(clientSource->surname);
    clientData->priceForDay = clientSource->priceForDay;
    clientData->id = clientSource->id;
    strcpy(clientData->rentDate, clientSource->rentDate);
    strcpy(clientData->rentHour, clientSource->rentHour);
    clientData->rentedCarLicense = clientSource->rentedCarLicense;
    return 1;
}



/*free allocated memory*/
void freeClient(Data data){
    FREE(((Client*)(data))->name);
    FREE(((Client*)(data))->surname);
}


/*gets rent date from user, prints name and surname of clients that rented a car in this date.*/
void printClientCarsForGivenRentDate(Node node) {
    linkedList clients;
    char userInput[11];
    int flag;
    if(!node){
        return;
    }

    clients = ALLOC(struct linkedList,1);
    clients->head = NULL;
    clients->comp = dateCompare;

    /*gets input from user*/
    puts("please enter a rent date to check: ");
    fillFieldStr(userInput, 10, 3, 1);

    flag = findNode(node, userInput, clients, &(clients->head));
    if (!flag) {
        puts("\n\tno clients found...");
    }
    else{
        printf("clients who rented a car at %s:\n", userInput);
        printClientList(clients->head);
    }
    freeList(clients);
}


/*gets searching parameter, and input from user.
 * returns linked list struct with all founded clients */
linkedList findClient(Node root){
    linkedList clients;
    int userChoice;
    double idInput;
    char dateInput[11];

    if(!root){
        return NULL;
    }

    clients = ALLOC(struct linkedList,1);
    clients->head = NULL;

    puts("how would you like to search for client?\n"
         "\t 1. by ID."
         "\t2. by rent date."
         "\tany other number to exit.");

    fillFieldInt(&userChoice,1,1,1);
    switch (userChoice) {
        case 1:
            puts("please enter a client's ID to search: ");
            fillFieldDouble(&idInput, 9, 1);
            clients->comp = clientsIdCompare;
            findNode(root, &idInput, clients, &(clients->head));
            break;
        case 2:
            puts("please enter a rent date to search: ");
            fillFieldStr(dateInput, 10, 3,1);
            clients->comp = &dateCompare;
            findNode(root, dateInput, clients, &(clients->head));

            break;
        default:
            return NULL;
    }
    return clients;
}


/*prints all clients names in linked list*/
void printClientList(nodeList node){
    nodeList temp;
    if (!node){
        return;
    }
    temp = node;
    while (temp){
        printf("client name: %s %s\n",((Client *)temp->data)->name,((Client *)temp->data)->surname);
        temp=temp->next;
    }
}

/*using generic function addNewNode to add new client to the clients tree*/
int addNewClient(Tree tree){
    return addNewNode(tree);
}

/*using generic function treeCreate to initialize new clients tree.*/
Tree createClientTree(){
    return treeCreate(clientCopy, freeClient, clientCompare, setClientData);
}

/*using generic function deleteNode to remove client node from the tree.*/
void deleteClient(Tree tree){
    double userInput = 0;
    int temp =0;

    if (!tree->root) {
        puts("client tree is empty");
        return;
    }
    /*gets input from user*/
    puts("please enter ID for the client you wish to delete (9 digits):");
    fillFieldDouble(&userInput, 9, 1);

    temp = tree->size;
    tree->root= deleteNode(tree, tree->root, &userInput, clientsIdCompare);
    if (tree->size < temp) {
        puts("client deleted from data base");
    }
    else puts("couldn't find client's ID ");
}

/*using generic function deleteAllNodes to remove all clients from the tree and free all allocating memory.*/
int deleteAllClients(Tree tree){
    freeAllNodes(tree, tree->root);
    tree->size = 0;
    tree->root = NULL;
    puts("deleting all clients......\n"
         "all clients deleted!");
    return 1;
}

/*print all the fields of given client*/
void printClientData(Data data){
    printf("    \nName:  %s\n",((Client *)data)->name);
    printf("    Last Name:  %s\n",((Client *)data)->surname);
    printf("    ID:  %0.f\n",((Client *)data)->id);
    printf("    client's rented car license:  %0.f\n",((Client *)data)->rentedCarLicense);
    printf("    renting date:  %s\n",((Client *)data)->rentDate);
    printf("    renting hour:  %s\n",((Client *)data)->rentHour);
    printf("    price per day: %0.f\n",((Client *)data)->priceForDay);
}
