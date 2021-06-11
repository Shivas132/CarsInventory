#include "menu.h"

int main(){

    clientBST *clientTree;
    carBST * carTree;
    supplierBST * supplierTree;

    carTree = createCarTree();
    clientTree = createClientTree();
    supplierTree = createSupplierTree();


    menu(carTree,supplierTree,clientTree);


    return 0;
}
