#include "menu.h"


int main(){
        Tree carTree = createCarTree();
        Tree supplierTree = createSupplierTree();

        /*addNewNode(carTree);
        addNewNode(carTree);
        addNewNode(carTree);*/

        addNewSupplier(supplierTree);
        addNewSupplier(supplierTree);
        addNewSupplier(supplierTree);




        printTree(supplierTree->root,printSupplierNode);
        averageOfSupplierMoney(supplierTree);
        threeGreatestSuppliers(supplierTree);
        check_for_exit();
        deleteSupplier(supplierTree);
        check_for_exit();
        deleteAllSuppliers(supplierTree);
        check_for_exit();


        return 0;
}
