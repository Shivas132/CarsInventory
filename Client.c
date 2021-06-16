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

/*copying data to new node.*/
int copyClient_list(nodeList dest, Client source){
    Client* clientData = ((Client*)dest->data);

    clientData->name = copyField(source.name);
    clientData->surname = copyField(source.surname);
    clientData->priceForDay = source.priceForDay;
    clientData->id = source.id;
    strcpy(clientData->rentDate, source.rentDate);
    strcpy(clientData->rentHour, source.rentHour);
    clientData->rentedCarLicense = source.rentedCarLicense;
    return 1;
}

/*creates new list node.*/
/*clientNode_l *createNode_l(Client client){
    clientNode_l * new = ALLOC(clientNode_l,1);
    new->next = NULL;
    copyClient_list(new, client);
    return new;
}*/

/*finds a client by binary search for given id.*/
int findClientByID(clientNode* tree, double id, clientNode_l** head){

    if(!tree){
        return 0;
    }
    if(tree->client.id == id){
        *head = createClientNode_l(tree->client);
        return 1;
    }
    if(tree->client.id > id){
        return findClientByID(tree->left , id, head);
    }
    return findClientByID(tree->right , id, head);
}

/*insert a node in linked list.*/
int insertNewNode(clientNode_l** head, Client client){
    clientNode_l *newNode = NULL, *curr;

    /*initializing new node. */
    newNode = createClientNode_l(client);

    /*true when list is empty, or client's id is smaller then first node's*/
    if ((*head == NULL) || (*head)->client.id >= client.id) {
        newNode->next = *head;
        *head = newNode;
        return 1;
    }

    /*finds the first bigger client id*/
    curr = *head;
    while ((curr->next) && (curr->next->client.id < newNode->client.id)) {
        curr = curr->next;
    }

    /*inserting the new node after the current one.*/
    newNode->next = curr->next;
    curr->next = newNode;
    return 1;
}

/*finds client and insert them to a linked list.*/
int findClientByRentDate(clientNode* tree, const char* date, clientNode_l** head){
    if(!tree){
        return 0;
    }
    if(strcmp(tree->client.rentDate, date) == 0) {
        insertNewNode(head, tree->client);
    }
    findClientByRentDate(tree->left, date, head);
    findClientByRentDate(tree->right, date, head);
    return 1;
}

/*gets searching parameter, and input from user.
 * returns all clients that*/
clientList* findClient(clientNode* tree){
    clientList *clients;
    int userChoice;
    double idInput;
    char dateInput[11];

    if(!tree){
        return NULL;
    }

    clients = ALLOC(clientList,1);
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
            findClientByID(tree, idInput, (&clients->head));
            break;
        case 2:
            puts("please enter a rent date to search: ");
            fillFieldStr(dateInput, 10, 3,1);
            findClientByRentDate(tree, dateInput, (&clients->head));
            break;
        default:
            return NULL;
    }
    return clients;
}

/*free allocated memory of linked list*/
int clearClientsList(clientList* list){
    clientNode_l * temp;

    while (list->head){
        temp = list->head->next;
        FREE(list->head->client.name);
        FREE(list->head->client.surname);
        FREE(list->head);
        list->head = temp;
    }
    FREE(list);
    return 1;
}

/*prints clients names in liked list*/
void printClientList(clientList* list){
    clientNode_l * temp;
    if (!list){
        return;
    }
    temp=list->head;
    while (temp){
        printf("client name: %s %s\n",temp->client.name,temp->client.surname);
        temp=temp->next;
    }
}






