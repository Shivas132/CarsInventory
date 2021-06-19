#include "menu.h"


int main(){


    Tree clientTree = createClientTree();
    Tree carTree = createCarTree();
    Tree supplierTree = createSupplierTree();

    menu(carTree, supplierTree, clientTree);



    return 0;
}
