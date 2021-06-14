#include "menu.h"

int main(){

    Tree tree = createCarTree();
    addNewNode(tree);
     addNewNode(tree);
     addNewNode(tree);


    check_for_exit();
    treeClear(tree, tree->root);
    check_for_exit();




    /*
    clientBST *clientTree;
    carBST * carTree;
    supplierBST * supplierTree;

    carTree = createCarTree();
    clientTree = createClientTree();
    supplierTree = createSupplierTree();


    menu(carTree,supplierTree,clientTree);*/


    return 0;
}
