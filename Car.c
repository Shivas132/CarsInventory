#include "Car.h"
#include <string.h>
#include "FillField.h"

/*allocating new binary search tree pointer. sets values to 0.*/
carBST* createCarTree(){
    carBST* newTree;
    newTree = ALLOC(carBST , 1);
    newTree->root = NULL;
    newTree->size = 0;
    return newTree;
}

/*help function to call in addNewCar. orders root by license number*/
carNode* appendCarToTree(carNode* root, Car new_car, carBST* carTree){
    carNode* newNode;
    if(!root){
        /*allocating new node. increasing size.*/
        newNode = ALLOC(carNode ,1);
        newNode->car = new_car;
        newNode->left = newNode->right = NULL;
        puts("Car added to tree!");
        carTree->size+=1;
        return newNode;
    }

    /*prevent license number duplication*/
    if(new_car.licenseNum == root->car.licenseNum) {
        puts("License number already exists in Data Base.");
        return root;
    }
    if(new_car.licenseNum < root->car.licenseNum) /* Go left*/
        root->left = appendCarToTree(root->left, new_car, carTree);
    else{ /* Go right*/
        root->right = appendCarToTree(root->right, new_car, carTree);
    }
    return root;
}

/*adds new car to the cars tree.*/
int addNewCar(carBST* tree) {
    Car new_car;
    double licenseNum;
    char chassisNum[6];
    int manufactorYear;
    int onRoadSince;
    double priceFromSupplier;
    double currentPrice;
    int velocity;

    printf("please enter details for your new car:\n");

    /*setting user inputs to fields
     * checking input validation*/
    puts("please enter licence number (7 digits):");
    fillFieldDouble(&licenseNum, 7, 1);
    new_car.licenseNum = licenseNum;

    puts("please enter chassis number (5 digits): ");
    fillFieldStr(chassisNum, 5, 1, 1);
    strcpy(new_car.chassisNum, chassisNum);

    puts("please enter manufacturer name: ");
    new_car.manufacturer = fillFiledStrDynamic(2);

    puts("please enter model name: ");
    new_car.model = fillFiledStrDynamic(2);

    puts("please enter car's color: ");
    new_car.color = fillFiledStrDynamic(2);

    puts("please enter manufacturing year (4 digits): ");
    fillFieldInt(&manufactorYear, 4, 1,5);
    new_car.manufactorYear = manufactorYear;

    puts("please enter ascension year (4 digits): ");
    fillFieldInt(&onRoadSince, 4, 1,5);
    new_car.onRoadSince = onRoadSince;

    puts("please enter price from supplier (7 digits max): ");
    fillFieldDouble(&priceFromSupplier, 7, 0);
    new_car.priceFromSupplier = priceFromSupplier;

    puts("please enter current price (7 digits max): ");
    fillFieldDouble(&currentPrice, 7, 0);
    new_car.currentPrice = currentPrice;

    puts("please enter engine's velocity (4 digits): ");
    fillFieldInt(&velocity, 4, 1,1);
    new_car.velocity = velocity;

    /*creates new node and puts it in the tree*/
    tree->root = appendCarToTree(tree->root, new_car, tree);

    return 1;
}

/*free allocated memory*/
int freeCar(carNode* node){
    if(node) {
        FREE(node->car.manufacturer);
        FREE(node->car.color);
        FREE(node->car.model);
        FREE(node);
    }
    return 1;
}

/*copying data to destination node.
 * allocating new memory for dynamic allocated data copying.*/
int deepCopyCarFields(carNode* dest, Car source){
    freeCar(dest);
    dest->car.manufacturer = copyField(source.manufacturer);
    dest->car.color = copyField(source.color);
    dest->car.model = copyField(source.model);
    dest->car.licenseNum = source.licenseNum;
    dest->car.manufactorYear = source.manufactorYear;
    dest->car.velocity = source.velocity;
    dest->car.onRoadSince = source.onRoadSince;
    dest->car.currentPrice = source.currentPrice;
    dest->car.priceFromSupplier = source.priceFromSupplier;
    strcpy(dest->car.chassisNum, source.chassisNum);

    return 1;
}

/*delete carNode by given license number*/
/*license parameter always starts as 0.*/
carNode* deleteCar(carNode* tree, double license,carBST* bst){
    carNode *temp, *follower, **followerAddr;
    double userInput = 0;
    if (!tree) {
        return NULL;
    }

    /*gets input from user*/
    if(license == 0){
        puts("please enter license num for the car you wish to delete:");
        fillFieldDouble(&userInput, 7, 1);
    }
    else{
        userInput = license;
    }
    /* searching wanted car in tree's children*/
    if(tree->car.licenseNum != userInput) {
        /* Go left*/
        if( userInput < (tree->car.licenseNum)) {
            tree->left = deleteCar(tree->left, userInput,bst);
        }
        /* Go right*/
        else {
            tree->right = deleteCar(tree->right, userInput,bst);
        }
    }
    else {

/* Option 1: tree is a leaf*/
        if (!(tree->left) && !(tree->right)) {
            freeCar(tree);
            bst->size -= 1;
            return NULL;
        }
/* Option 2: tree has only one child*/
        else if (!(tree->left)) {
            temp = tree->right;
            freeCar(tree);
            bst->size -= 1;
            return temp;
        } else if (!(tree->right)) {
            temp = tree->left;
            freeCar(tree);
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
            deepCopyCarFields(tree, follower->car);
            *followerAddr = deleteCar(follower, follower->car.licenseNum,bst);
        }
    }
    return tree;
}

/*help function for deleteAllCars.
 * free all the nodes from the tree.*/
int deleteAllcarsNodes(carNode* tree){
    if(!tree){
        return 1;
    }
    /*free children first*/
    deleteAllcarsNodes(tree->left);
    deleteAllcarsNodes(tree->right);
    freeCar(tree);
    return 1;
}

/*clears all tree nodes, sets values to 0.*/
int deleteAllCars(carBST* tree){
    deleteAllcarsNodes(tree->root);
    tree->root = NULL;
    tree->size = 0;
    return 1;
}


/*returns the number of cars in the list with a given capacity*/
/*cap parameter always starts as 0.*/
int carNumberWithGivenCapacity(carNode* root, int cap){
    int userInput, res = 0;

    if(!root){
        return 0;
    }

    /*gets input from user*/
    if(cap == 0) {
        puts("please enter a capacity for the check: ");
        fillFieldInt(&userInput, 4, 1, 1);
    }
    else{
        userInput = cap;
    }

    /*increasing result by 1*/
    if(root->car.velocity == userInput){
        res++;
    }

    /*sums results of children*/
    res += carNumberWithGivenCapacity(root->left, userInput);
    res += carNumberWithGivenCapacity(root->right, userInput);

    return res;
}








