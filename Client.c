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

int addNewClient(Tree tree){
    return addNewNode(tree);
}

/*free allocated memory*/
void freeClient(Data data){
    FREE(((Client*)(data))->name);
    FREE(((Client*)(data))->surname);
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

double clientCompare(void * id1,void * id2){ /*TODO maybe generic?*/
    return *(double*)id1-*(double*)id2;
}

/*allocating new binary search tree pointer. sets values to 0.*/
Tree createClientTree(){
    return treeCreate(clientCopy, freeClient, clientCompare, setClientData);
}

int deleteClient(Tree tree){
    double* userInput = 0;

    /*gets input from user*/
    puts("please enter id for the client you wish to delete: (9 digits)");
    fillFieldDouble(userInput, 9, 1);

    deleteNode(tree, tree->root, userInput);
    return 1;
}

int deleteAllClients(Tree tree){
    freeAllNodes(tree, tree->root);
    tree->size = 0;
    return 1;
}



/*recursive function. every call it compares client's rent date and prints it's name if true.
 * returns flag to indicate if any client found.*/
int printClientCarsForGivenRentDate_rec(clientNode* tree, char* userInput){
    int flag = 0;

    /*base case - empty pointer*/
    if (!tree) {
        return 0;
    }

    /*prints client's name and surname*/
    if (strcmp(userInput, tree->client.rentDate) == 0) {
        printf("\t%s %s\n", tree->client.name, tree->client.surname);
        flag =1;
    }

    /*goes to tree's children*/
    flag += printClientCarsForGivenRentDate_rec(tree->left, userInput);
    flag += printClientCarsForGivenRentDate_rec(tree->right, userInput);
    return flag;
}


/*gets rent date from user, prints name and surname of clients that rented a car in this date.*/
void printClientCarsForGivenRentDate(clientNode * tree) {

    char userInput[11];
    int flag;

    /*gets input from user*/
    puts("please enter a rent date to check: ");
    fillFieldStr(userInput, 10, 3, 1);

    printf("clients who rented a car at %s:\n", userInput);
    flag = printClientCarsForGivenRentDate_rec(tree, userInput);
    if (!flag) {
        puts("\n\tno clients found...");
    }
}


/*---------------------findClient functions---------------------*/

double dateCompare(void* date1, void* date2){
    return strcmp((char*)(date1), (char*)(date2));
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
            clients->comp = &clientCompare;
            findNode(root, &idInput, clients, &(clients->head));
            break;
        case 2:
            puts("please enter a rent date to search: ");
            fillFieldStr(dateInput, 10, 3,1);
            findNode(root, dateInput, clients, &(clients->head));
            clients->comp = &dateCompare;
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






