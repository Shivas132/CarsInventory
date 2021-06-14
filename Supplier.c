#include "Supplier.h"
#include <string.h>
#include "FillField.h"
#include "BinarySearchTree.h"
#include <stdio.h>

/*allocating new binary search tree pointer. sets values to 0.*/
supplierBST * createSupplierTree(){
    supplierBST * newTree;
    newTree = ALLOC(supplierBST, 1);
    newTree->root = NULL;
    newTree->size = 0;
    return newTree;
}

/*help function to call in addNewSupplier. orders tree by IDs*/
supplierNode * appendSupplierToTree(supplierNode * tree, Supplier newSupplier,supplierBST* supplierBst){
    supplierNode * newNode;
    if(!tree){
        /*allocating new node. increasing size.*/
        newNode = ALLOC(supplierNode ,1);
        newNode->supplier = newSupplier;
        newNode->left = newNode->right = NULL;
        puts("supplier added to Data Base.");
        supplierBst->size += 1;
        return newNode;
    }

    /*prevent ID duplication*/
    if(newSupplier.id == tree->supplier.id) {
        puts("ID already exists in Data Base.");
        return tree;
    }
    if(newSupplier.id < tree->supplier.id) /* Go left*/
        tree->left = appendSupplierToTree(tree->left, newSupplier,supplierBst);
    else /* Go right*/
        tree->right = appendSupplierToTree(tree->right, newSupplier,supplierBst);

    return tree;
}

/*adds new supplier to the head of suppliers list.*/
int addNewSupplier(supplierBST* tree){
    Supplier new_supplier;
    double  id;
    char  phoneNumber[11];
    double pastTransactionsNumber;
    double pastTransactionsSum;

    printf("please enter details for your new supplier: \n");

    /*setting user inputs to fields
     * checking input validation*/
    puts("please enter supplier's id (10 digits): ");
    fillFieldDouble(&id, 10, 1);
    new_supplier.id= id;

    puts("please enter supplier's name: ");
    new_supplier.name = fillFiledStrDynamic(2);

    puts("please enter supplier's phone number (10 digits): ");
    fillFieldStr(phoneNumber, 10, 1, 1);
    strcpy(new_supplier.phoneNumber, phoneNumber);

    puts("please enter number of transactions (5 digits): ");
    fillFieldDouble(&pastTransactionsNumber, 5, 1);
    new_supplier.pastTransactionsNumber = pastTransactionsNumber;

    puts("please enter sum of transactions (10 digits): ");
    fillFieldDouble(&pastTransactionsSum, 10, 1);
    new_supplier.pastTransactionsSum = pastTransactionsSum;

    /*creates new node and puts it in the tree*/
    tree->root = appendSupplierToTree(tree->root, new_supplier,tree);
    return 1;
}

/*free allocated memory*/
int freeSupplier(supplierNode * node){
    FREE(node->supplier.name);
    FREE(node);
    return 1;
}

/*copying data to destination node.
 * allocating new memory for dynamic allocated data copying.*/
int deepCopySuppliersFields(supplierNode * dest, Supplier source){
    freeSupplier(dest);
    dest->supplier.name = copyField(source.name);
    dest->supplier.pastTransactionsSum = source.pastTransactionsSum;
    dest->supplier.pastTransactionsNumber= source.pastTransactionsSum;
    dest->supplier.id=source.id;
    strcpy(dest->supplier.phoneNumber, source.phoneNumber);
    return 1;
}

/*delete supplierNode by given id*/
/*id parameter always starts as 0.*/
supplierNode * deleteSupplier(supplierNode * tree, double id, supplierBST* bst){
    supplierNode *temp, *follower, **followerAddr;
    double userInput = 0;

    if (!tree) {
        return NULL;
    }
    /*gets input from user*/
    if(id == 0){
        puts("please enter id for the supplier you wish to delete:");
        fillFieldDouble(&userInput, 10, 1);
    }
    else{
        userInput = id;
    }

    /* searching wanted supplier in tree's children*/
    if(tree->supplier.id != userInput) {
        /* Go left*/
        if( userInput < (tree->supplier.id)) {
            tree->left = deleteSupplier(tree->left, userInput, bst);
        }
            /* Go right*/
        else {
            tree->right = deleteSupplier(tree->right, userInput, bst);
        }

    }

    else {

/* Option 1: tree is a leaf*/
        if (!(tree->left) && !(tree->right)) {
            freeSupplier(tree);
            bst->size -= 1;
            return NULL;
        }
/* Option 2: tree has only one child*/
        else if (!(tree->left)) {
            temp = tree->right;
            freeSupplier(tree);
            bst->size -= 1;
            return temp;
        } else if (!(tree->right)) {
            temp = tree->left;
            freeSupplier(tree);
            bst->size -= 1;
            return temp;
        }
/* Option 3: tree has 2 children*/
        else {
            follower = tree->right;
            followerAddr = &(tree->right);
            while (follower->left) {
                followerAddr = &(follower->left);
                follower = follower->left;
            }
            deepCopySuppliersFields(tree, follower->supplier);
            *followerAddr = deleteSupplier(follower, follower->supplier.id, bst);
        }
    }
    return tree;
}

/*help function for deleteAllSuppliers.
 *free all the nodes from the tree.*/
int deleteAllNodesSupplier(supplierNode * tree){
    if(!tree){
        return 1;
    }
    /*free children first*/
    deleteAllNodesSupplier(tree->left);
    deleteAllNodesSupplier(tree->right);
    freeSupplier(tree);
    return 1;
}

/*clears all tree nodes, sets values to 0.*/
int deleteAllSuppliers(supplierBST * tree){
    deleteAllNodesSupplier(tree->root);
    tree->root =NULL;
    tree->size = 0;
    return 1;
}

/*bubble sorting the current list of three greatest suppliers.*/
void threeGreatestSupplierBubble(Supplier*  greatest){
    int i,j;
    Supplier temp;
    for (i=0;i<2;i++){
        for (j=i+1;j<3;j++){
            if (greatest[i].pastTransactionsSum>greatest[j].pastTransactionsSum){
                temp = greatest[i];
                greatest[i] = greatest[j];
                greatest[j] = temp;
            }
        }
    }
}

/*help function for threeGreatestSuppliers.
 *adds supplier to the array if it's in the current three greatest.*/
void addToGreatest(Supplier* greatest,supplierNode* tree){
    if (!tree){
        return;
    }
    if (tree->supplier.pastTransactionsSum>greatest[0].pastTransactionsSum){
        greatest[0]=tree->supplier;
        /*keeps the array sorted every call.*/
        threeGreatestSupplierBubble(greatest);
    }
    addToGreatest(greatest,tree->left);
    addToGreatest(greatest,tree->right);
}

/*creates and prints an array, containing the id of the 3 suppliers with the highest pastTransactionsSum*/
int threeGreatestSuppliers(supplierBST tree){
    Supplier greatest[3];
    int i;
    if (tree.size<3){
        puts("there are less then three suppliers in the list");
        return -1;
    }
    for (i = 0; i < 3; i++) {
        greatest[i].pastTransactionsSum=0;}
    addToGreatest(greatest,tree.root);
    puts("three greatest suppliers are:");
    for(i = 0; i < 3; i++){
        printf("%d:  %.0f\n",i+1,greatest[i].id);}
    return 1;
}

/*returns the average of past transactions sum of all suppliers in tree.*/
double averageOfSupplierMoney(supplierNode* tree ,int n){
    double res;
    if (!tree){
        return 0;
    }
    res =(tree->supplier.pastTransactionsSum)/n;
    res += averageOfSupplierMoney(tree->left,n);
    res += averageOfSupplierMoney(tree->right,n);
    return res;
}


/*prints every supplier's details in the list*/
void printSupplierNode(Node  node){
    printf("    \nName:  %s\n",((Supplier*)node->data)->name);
    printf("    Supplier's authorized dealer number:  %0.f\n",((Supplier*)node->data)->id);
    printf("    Phone number:  %s\n",((Supplier*)node->data)->phoneNumber);
    printf("    Number of past transaction with supplier  :%0.f\n",((Supplier*)node->data)->pastTransactionsNumber);
    printf("    Sum of past transaction with supplier  :%0.f\n",((Supplier*)node->data)->pastTransactionsSum);

}

double getSupplierAvgField(Node node){
    return ((Supplier*)node->data)->pastTransactionsSum;
}
