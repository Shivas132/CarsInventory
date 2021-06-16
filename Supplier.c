#include "Supplier.h"
#include <string.h>
#include "FillField.h"
#include "GenericDataStructures.h"
#include <stdio.h>

/*adds new supplier to the head of suppliers list.*/
Data setSupplierData(){
    Supplier* new_supplier;
    double  id;
    char  phoneNumber[11];
    double pastTransactionsNumber;
    double pastTransactionsSum;
    new_supplier = ALLOC(Supplier, 1);

    printf("please enter details for your new supplier: \n");

    /*setting user inputs to fields
     * checking input validation*/
    puts("please enter supplier's id (10 digits): ");
    fillFieldDouble(&id, 10, 1);
    new_supplier->id= id;

    puts("please enter supplier's name: ");
    new_supplier->name = fillFiledStrDynamic(2);

    puts("please enter supplier's phone number (10 digits): ");
    fillFieldStr(phoneNumber, 10, 1, 1);
    strcpy(new_supplier->phoneNumber, phoneNumber);

    puts("please enter number of transactions (5 digits): ");
    fillFieldDouble(&pastTransactionsNumber, 5, 1);
    new_supplier->pastTransactionsNumber = pastTransactionsNumber;

    puts("please enter sum of transactions (10 digits): ");
    fillFieldDouble(&pastTransactionsSum, 10, 1);
    new_supplier->pastTransactionsSum = pastTransactionsSum;

    return new_supplier;
}

int addNewSupplier(Tree tree){
    return addNewNode(tree);
}

/*free allocated memory*/
void freeSupplier(Data data){
    FREE(((Supplier *)(data))->name);
}

/*copying data to destination node.
 * allocating new memory for dynamic allocated data copying.*/
int supplierCopy(Node dest, Data source){
    Supplier * supData = ((Supplier *)dest->data);
    Supplier * supSource = ((Supplier *)source);

    supData->name = copyField(supSource->name);
    supData->pastTransactionsSum = supSource->pastTransactionsSum;
    supData->pastTransactionsNumber= supSource->pastTransactionsSum;
    supData->id = supSource->id;
    strcpy(supData->phoneNumber, supSource->phoneNumber);
    return 1;
}

double supplierCompare(void * id1,void * id2){
    return *(double*)id1-*(double*)id2;
}

/*allocating new binary search tree pointer. sets values to 0.*/
Tree createSupplierTree(){
    return treeCreate(supplierCopy, freeSupplier, supplierCompare, setSupplierData);
}

int deleteSupplier(Tree tree){
    double* userInput = 0;

    /*gets input from user*/
    puts("please enter id for the supplier you wish to delete:");
    fillFieldDouble(userInput, 10, 1);

    deleteNode(tree, tree->root, userInput);
    return 1;
}

int deleteAllSuppliers(Tree tree){
    freeAllNodes(tree, tree->root);
    tree->size = 0;
    return 1;
}


/*bubble sorting the current list of three greatest suppliers.*/
void threeGreatestSupplierBubble(Supplier*  greatest){
    int i,j;
    Supplier temp;
    for (i=0;i<2;i++){
        for (j=i+1;j<3;j++){
            if (greatest[i].pastTransactionsSum>greatest[j].pastTransactionsSum){
                temp = greatest[i];
                greatest[i] = greatest[j];
                greatest[j] = temp;
            }
        }
    }
}

/*help function for threeGreatestSuppliers.
 *adds supplier to the array if it's in the current three greatest.*/
void addToGreatest(Supplier* greatest,Node node){
    Supplier currSupplier = *((Supplier*)node);
    if (!node){
        return;
    }
    if (currSupplier.pastTransactionsSum>greatest[0].pastTransactionsSum){
        greatest[0]=currSupplier;
        /*keeps the array sorted every call.*/
        threeGreatestSupplierBubble(greatest);
    }
    addToGreatest(greatest,node->left);
    addToGreatest(greatest,node->right);
}

/*creates and prints an array, containing the id of the 3 suppliers with the highest pastTransactionsSum*/
int threeGreatestSuppliers(Tree tree){
    Supplier greatest[3];
    int i;
    if (tree->size<3){
        puts("there are less then three suppliers in the list");
        return -1;
    }
    for (i = 0; i < 3; i++) {
        greatest[i].pastTransactionsSum=0;}
    addToGreatest(greatest,tree->root);
    puts("three greatest suppliers are:");
    for(i = 0; i < 3; i++){
        printf("%d:  %.0f\n",i+1,greatest[i].id);}
    return 1;
}

/*print the average of past transactions sum of all suppliers in tree.*/
void averageOfSupplierMoney(Tree supplierTree) {
        printf("%f",averageTree(supplierTree,supplierTree->root,getPastTransactionsSum));
}


/*prints supplier's details*/
void printSupplierNode(Node  node){
    printf("    \nName:  %s\n",((Supplier*)node->data)->name);
    printf("    Supplier's authorized dealer number:  %0.f\n",((Supplier*)node->data)->id);
    printf("    Phone number:  %s\n",((Supplier*)node->data)->phoneNumber);
    printf("    Number of past transaction with supplier  :%0.f\n",((Supplier*)node->data)->pastTransactionsNumber);
    printf("    Sum of past transaction with supplier  :%0.f\n",((Supplier*)node->data)->pastTransactionsSum);

}

double getPastTransactionsSum(Node node){

    return ((Supplier*)node->data)->pastTransactionsSum;
}


