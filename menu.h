#include "DataBase.h"

#ifndef HW3_MENU_H
#define HW3_MENU_H

void menu(carBST * carTree , supplierBST * supplierTree, clientBST * clientTree);

/*helpers for menu*/
void carSwitch(int carChoose,carBST * carTree);
void clientSwitch(int clientChoose, clientBST * clientTree,carNode* carRoot);
void supplierSwitch(int supplierChoose,supplierBST * supplierTree);

#endif
