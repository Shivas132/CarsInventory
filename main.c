#include "menu.h"

void printo(Tree clientTree){
    printf("root %0.f\n",((Client*)clientTree->root->data)->id);
    if (clientTree->root->left){
        printf("left %0.f\n",((Client*)clientTree->root->left->data)->id);
    }
    if (clientTree->root->right){
        printf("right %0.f\n",((Client*)clientTree->root->right->data)->id);
    }
}
int main(){


    Tree clientTree = createClientTree();

    addNewClient(clientTree);
    addNewClient(clientTree);
    addNewClient(clientTree);

    deleteClient(clientTree);
    printo(clientTree);
    deleteClient(clientTree);
    printo(clientTree);
    deleteClient(clientTree);
    printo(clientTree);


    return 0;
}
