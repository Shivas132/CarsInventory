#include "Client.h"
#include <string.h>
#include "FillField.h"
#include <stdio.h>

/*adds new client to the head of clients list.*/
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

double clientCompare(void * client1,void * client2){
    return ((Client *)client1)->id-((Client *)client2)->id;
}

/*free allocated memory*/
void freeClient(Data data){
    FREE(((Client*)(data))->name);
    FREE(((Client*)(data))->surname);
    FREE(data);
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
    clients->fre = &freeClient;

    /*gets input from user*/
    puts("please enter a rent date to check: ");
    fillFieldStr(userInput, 10, 3, 1);

    printf("clients who rented a car at %s:\n", userInput);
    flag = findNode(node, userInput, clients, &(clients->head));
    if (!flag) {
        puts("\n\tno clients found...");
    }
    else{
        printClientList(clients->head);
    }
    freeList(clients);
}


/*---------------------findClient functions---------------------*/

double dateCompare(void* client, void* date){
    return strcmp(((Client*)(client))->rentDate, (char*)date);
}
double idCompare(void* client, void* id){
    return ((Client*)(client))->id- *((double *)id);
}

/*gets searching parameter, and input from user.
 * returns all clients that*/
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
    clients->fre = &freeClient;

    puts("how would you like to search for client?\n"
         "\t 1. by ID."
         "\t2. by rent date."
         "\tany other number to exit.");

    fillFieldInt(&userChoice,1,1,1);
    switch (userChoice) {
        case 1:
            puts("please enter a client's ID to search: ");
            fillFieldDouble(&idInput, 9, 1);
            clients->comp = &idCompare;
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


/*prints clients names in liked list*/
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

int addNewClient(Tree tree){
    return addNewNode(tree);
}


/*allocating new binary search tree pointer. sets values to 0.*/
Tree createClientTree(){
    return treeCreate(clientCopy, freeClient, clientCompare, setClientData);
}

Node deleteClient(Tree tree){
    double userInput = 0;

    /*gets input from user*/
    puts("please enter id for the client you wish to delete: (9 digits)");
    fillFieldDouble(&userInput, 9, 1);


    return deleteNode(tree, tree->root, &userInput);
}

int deleteAllClients(Tree tree){
    freeAllNodes(tree, tree->root);
    tree->size = 0;
    tree->root = NULL;
    puts("deleting all clients......\n"
         "all clients deleted!");
    return 1;
}





