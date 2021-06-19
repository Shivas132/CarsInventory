#include "menu.h"
#include <stdio.h>

void menu(Tree  carTree , Tree supplierTree, Tree clientTree){
    int choose,carChoose,clientChoose,supplierChoose,exitChoose;
    puts("Welcome to CarsOrganizer \n(BETA version)");
    puts("initializing data base \ncreating cars tree.....\tdone!\tcreating suppliers tree.....\tdone!\tcreating clients tree.....\tdone!\n");
    while(1){
        puts("\nplease enter your choose:\n"
             "      1.Cars menu\n"
             "      2.clients menu\n"
             "      3.suppliers menu\n"
             "      0.exit.\n"
             "your choose: ");
        fillFieldInt(&choose,1,1,1);
        switch (choose) {
            case 1:
                puts("please enter your choose\n"
                     "      1.add new car\n"
                     "      2.delete Car\n"
                     "      3.get how many cars there are with given engine velocity\n"
                     "      4.generate an array made of the tree and print it\n"
                     "      0.delete all cars\n"
                     "      any other digit to return\n");
                fillFieldInt(&carChoose,1,1,1);
                carSwitch(carChoose, carTree);
                break;

            case 2:
                puts("please enter your choose\n"
                     "      1.add new client\n"
                     "      2.delete client\n"
                     "      3.find client\n"
                     "      4.print all clients with given rent date\n"
                     "      5.get how many client's there are with car from given car year\n"
                     "      6.generate an array made of the tree and print it\n"
                     "      0.delete all clients\n"
                     "      any other digit to return\n");
                fillFieldInt(&clientChoose,1,1,1);
                clientSwitch(clientChoose, clientTree,carTree->root);
                break;

            case 3:
                puts("please enter your choose\n"
                     "      1.add new supplier\n"
                     "      2.delete supplier\n"
                     "      3.get ID number of the top 3 suppliers\n"
                     "      4.average sum of deals with suppliers\n"
                     "      5.print all suppliers details\n"
                     "      6.generate an array made of the tree and print it\n"
                     "      0.delete all suppliers\n"
                     "      any other digit to return\n");
                fillFieldInt(&supplierChoose,1,1,1);
                supplierSwitch(supplierChoose, supplierTree);
                break;

            case 0:
                puts("Are you sure?\n"
                     "1.yes\n"
                     "any other choose for return")   ;
                fillFieldInt(&exitChoose,1,1,1);
                if (exitChoose==1){
                    freeTree(supplierTree);
                    freeTree(clientTree);
                    freeTree(carTree);
                    puts("checking data base status....");
                    puts("cleaning cars list.....\ndone!");
                    puts("cleaning suppliers list.....\ndone!");
                    puts("cleaning clients list.....\ndone!");
                    puts("you good to go!\nByeBye");
                    check_for_exit();
                    exit(0);}
                else{break;}
            default:
                continue;
        }
    }
}
void carSwitch(int carChoose,Tree carTree) {
    Data * arr;
    int temp;
    switch (carChoose) {
        case 1:
            addNewCar(carTree);
            break;
        case 2:
            deleteCar(carTree);
            break;
        case 3:
            temp = carNumberWithGivenCapacity(carTree->root,0);
            if (temp != 0){
                printf("there are %d cars with given capacity",temp);

            } else
                puts("there are no cars with given capacity");
            temp=-1;
            break;
        case 4:
            if (carTree->size>0) {
                arr = treeToArray(carTree);
                printArray(arr, printCarData,carTree->size);
                FREE(arr);
            }
            else puts("tree is empty");
            break;
        case 0:
            puts("Are you sure?\n"
                 "1.yes\n"
                 "any other choose for return");
            fillFieldInt(&temp,1,1,1);
            if (temp==1) {
                deleteAllCars(carTree);
                puts("deleting.....\n");
                puts("all cars deleted!");
                temp =-1;
            }
            break;
        default:
            break;
    }
}


void clientSwitch(int clientChoose,Tree clientTree,Node carRoot) {
    Data* arr;
    int temp = 0;
    linkedList found = NULL;
    switch (clientChoose) {
            case 1:
                addNewClient(clientTree);
                break;
            case 2:
                deleteClient(clientTree);
                    break;
            case 3:
                found = findClient(clientTree->root);
            if (!found->head){
                puts("client didn't found");}
            else{printClientList(found->head);
                 freeList(found);}
                break;
            case 4:
                printClientCarsForGivenRentDate(clientTree->root);
                break;
            case 5:
                temp = clientNumberWithGivenCarYear(carRoot, clientTree->root, 0);
                if (temp != 0) {
                    printf("there are %d clients who rented a car in given manufacturing year ", temp);
                } else {
                    puts("there are no clients who rented a car in given manufacturing year ");
                }
                temp = -1;
                break;
           case 6:
               if (clientTree->size>0) {
                   arr = treeToArray(clientTree);
                   printArray(arr, printClientData,clientTree->size);
                   FREE(arr);
               }
                else puts("tree is empty");
                break;
                case 0:
            puts("Are you sure?\n"
                 "1.yes\n"
                 "any other choose for return");
            fillFieldInt(&temp,1,1,1);
            if (temp==1) {
                puts("deleting.....\n");
                puts("all clients deleted!");
                deleteAllClients(clientTree);
                temp =-1;
            }
            break;
        default:
            break;
    }
}



void supplierSwitch(int supplierChoose, Tree supplierTree){
    int temp;
    Data * arr;
    switch (supplierChoose) {
        case 1:
            addNewSupplier(supplierTree);
            break;
        case 2:
            deleteSupplier(supplierTree);
            break;
        case 3:
            threeGreatestSuppliers(supplierTree);
            break;
        case 4:
            averageOfSupplierMoney(supplierTree);
            break;
        case 5:
            if (!supplierTree->root){
                puts("supplier tree is empty");
            }
            printSuppliers(supplierTree);
            break;
        case 6:
            if (supplierTree->size>0) {
                arr = treeToArray(supplierTree);
                printArray(arr, printSupplierData,supplierTree->size);
                FREE(arr);
            }
            else puts("tree is empty");
            break;
        case 0:
            puts("Are you sure?\n"
                 "1.yes\n"
                 "any other choose for return");
            fillFieldInt(&temp,1,1,1);
            if (temp==1) {
                puts("deleting.....\n");
                puts("all suppliers deleted!");
                deleteAllSuppliers(supplierTree);
                temp =-1;
            }
            break;
        default:
            break;
    }
}
