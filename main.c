#include "menu.h"


int main(){
    Tree carTree = createCarTree();
    Tree supplierTree = createSupplierTree();
    addNewNode(carTree);
    addNewNode(carTree);
    addNewNode(carTree);

    addNewNode(supplierTree);
    addNewNode(supplierTree);
    addNewNode(supplierTree);

    printTree(supplierTree->root,printSupplierNode);
    check_for_exit();
    freeTree(carTree);
    freeTree(supplierTree);
    check_for_exit();


    return 0;
}

return 0;
}
