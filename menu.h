#include "DataBase.h"

#ifndef HW3_MENU_H
#define HW3_MENU_H

void menu(Tree  carTree , Tree supplierTree, Tree clientTree);

/*helpers for menu*/
void carSwitch(int carChoose,Tree carTree);
void clientSwitch(int clientChoose,Tree clientTree,Node carRoot);
void supplierSwitch(int supplierChoose, Tree supplierTree);

#endif
