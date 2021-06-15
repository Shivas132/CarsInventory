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

typedef struct supplierNode_t{
    Supplier supplier;
    struct supplierNode_t* left;
    struct supplierNode_t* right;
}supplierNode;

typedef struct {
    supplierNode * root;
    int size;
} supplierBST;

/*creates empty supplierNode*/
Tree createSupplierTree();

int addNewSupplier(Tree tree);

int deleteSupplier(Tree tree);

int deleteAllSuppliers(Tree tree);

double averageOfSupplierMoney(supplierNode* tree ,int n);

int threeGreatestSuppliers(supplierBST tree);

void printSuppliers(supplierNode* tree);


#endif
