#include "menu.h"


int main(){

        Tree carTree = createCarTree();
        Tree supplierTree = createSupplierTree();
        Tree clientTree = createClientTree();


        menu(carTree,supplierTree,clientTree);


        return 0;
}
