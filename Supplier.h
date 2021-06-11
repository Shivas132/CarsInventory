#ifndef SUPPLIER_H
#define SUPPLIER_H

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
supplierBST * createSupplierTree();

int addNewSupplier(supplierBST * tree);

/*help function to call in addNewSupplier*/
supplierNode * appendSupplierToTree(supplierNode * tree, Supplier newSupplier,supplierBST* supplierBst);

supplierNode * deleteSupplier(supplierNode * tree, double id, supplierBST* bst);

int deleteAllSuppliers(supplierBST * tree);

double averageOfSupplierMoney(supplierNode* tree ,int n);

int threeGreatestSuppliers(supplierBST tree);

void printSuppliers(supplierNode* tree);


#endif
