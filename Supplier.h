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

void deleteSupplier(Tree tree);

int deleteAllSuppliers(Tree tree);

void averageOfSupplierMoney(Tree supplierTree);

int threeGreatestSuppliers(Tree tree);

void printSupplierData(Data data);

double getPastTransactionsSum(Node node);

void printSuppliers(Tree tree);

#endif
