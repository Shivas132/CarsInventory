#include "menu.h"


int main(){

        linkedList found;
        Tree clientTree = createClientTree();

        addNewClient(clientTree);
        addNewClient(clientTree);
        addNewClient(clientTree);



        found = findClient(clientTree->root);

        printClientList(found->head);
            freeList(found);

        found = findClient(clientTree->root);

        printClientList(found->head);
            freeList(found);

        printClientCarsForGivenRentDate(clientTree->root);
        deleteClient(clientTree);
        deleteAllClients(clientTree);
        freeTree(clientTree);
        check_for_exit();


        return 0;
}
