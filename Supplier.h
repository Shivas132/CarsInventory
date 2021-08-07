#ifndef SUPPLIER_H
#define SUPPLIER_H
#include "GenericDataStructures.h"

typedef struct Supplier{
    double  id;
    char*  name;
    char  phoneNumber[11];
    double pastTransactionsNumber;
    double pastTransactionsSum;
}Supplier;


/*using generic function treeCreate to initialize new supplier tree.*/
Tree createSupplierTree();

/*using generic function addNewNode to add new supplier to the suppliers tree*/
int addNewSupplier(Tree tree);

/*using generic function deleteNode to remove supplier node from the tree.*/
void deleteSupplier(Tree tree);

/*using generic function deleteAllNodes to remove all suppliers from the tree and free all allocating memory.*/
int deleteAllSuppliers(Tree tree);

/*print the average of past transactions sum of all suppliers in tree.
 * using generic function averageTree*/
void averageOfSupplierMoney(Tree supplierTree);

/*creates and prints an array, containing the licenseNum of the 3 suppliers with the highest pastTransactionsSum*/
int threeGreatestSuppliers(Tree tree);

void printSupplierData(Data data);

/*using generic function printTree to print every supplier in the suppliers tree*/
void printSuppliersTree(Tree tree);

#endif
