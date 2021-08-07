#include "Supplier.h"
#include <string.h>
#include "FillField.h"
#include "GenericDataStructures.h"
#include <stdio.h>

/*generate new supplier and getting all the information from the user
 *returns pointer to the new supplier as Data (void*)*/
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
    puts("please enter supplier's licenseNum (10 digits): ");
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

/*---------------------comparing functions---------------------*/

/*comparing between suppliers(Data)*/
double supplierCompare(Data supplier1,Data supplier2) {
    return ((Supplier *) supplier1)->id - ((Supplier *) supplier2)->id;
}
/*comparing between supplier(Data) and id(Double) */
double suppliersIdCompare(Data supplier, void* id){
    return ((Supplier *)(supplier))->id- *((double*)id);
}



/*using generic function deleteNode to remove supplier node from the tree.*/
void deleteSupplier(Tree tree){
    double userInput = 0;
    int temp =0;

    if (!tree->root) {
        puts("supplier tree is empty");
        return;
    }
    /*gets input from user*/
    puts("please enter ID for the supplier you wish to delete (10 digits):");
    fillFieldDouble(&userInput, 10, 1);

    temp =tree->size;
    tree->root= deleteNode(tree, tree->root, &userInput,suppliersIdCompare);
    if (tree->size < temp) {
        puts("supplier deleted from data base");
    }
    else puts("couldn't find supplier's ID ");
}

/*using generic function deleteAllNodes to remove all suppliers from the tree and free all allocating memory.*/
int deleteAllSuppliers(Tree tree){
    freeAllNodes(tree, tree->root);
    tree->size = 0;
    tree->root = NULL;
    puts("deleting all suppliers......\n"
         "all suppliers deleted!");
    return 1;
}


/*--------three greatest suppliers helpers--------*/

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

/*adds supplier to the array if it's in the current three greatest.*/
void addToGreatest(Supplier* greatest,Node node){
    Supplier currSupplier;
    if (!node){
        return;
    }
    currSupplier = *((Supplier*)node->data);

    if (currSupplier.pastTransactionsSum>greatest[0].pastTransactionsSum){
        greatest[0]=currSupplier;
        /*keeps the array sorted every call.*/
        threeGreatestSupplierBubble(greatest);
    }
    addToGreatest(greatest,node->left);
    addToGreatest(greatest,node->right);
}


/*creates and prints an array, containing the licenseNum of the 3 suppliers with the highest pastTransactionsSum*/
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

/*helper to averageOfSupplierMoney*/
double getPastTransactionsSum(Node node){
    return ((Supplier*)node->data)->pastTransactionsSum;
}

/*print the average of past transactions sum of all suppliers in tree.*/
void averageOfSupplierMoney(Tree supplierTree) {
        printf("average sum of deals with all suppliers is\n %.2f\n",averageTree(supplierTree,supplierTree->root,getPastTransactionsSum));
}

/*prints supplier's details*/
void printSupplierData(Data data){
    printf("    \nName:  %s\n",((Supplier*)data)->name);
    printf("    Supplier's authorized dealer number:  %0.f\n",((Supplier*)data)->id);
    printf("    Phone number:  %s\n",((Supplier*)data)->phoneNumber);
    printf("    Number of past transaction with supplier  :%0.f\n",((Supplier*)data)->pastTransactionsNumber);
    printf("    Sum of past transaction with supplier  :%0.f\n",((Supplier*)data)->pastTransactionsSum);
}


/*using generic function printTree to print every supplier in the suppliers tree*/
void printSuppliersTree(Tree tree){
    printTree(tree->root, printSupplierData);
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

/*using generic function addNewNode to add new supplier to the suppliers tree*/
int addNewSupplier(Tree tree){
    return addNewNode(tree);
}
/*free allocated memory*/
void freeSupplier(Data data){
    FREE(((Supplier *)(data))->name);
}

/*using generic function treeCreate to initialize new supplier tree.*/
Tree createSupplierTree(){
    return treeCreate(supplierCopy, freeSupplier, supplierCompare, setSupplierData);
}

