#include "Car.h"
#include <string.h>
#include "FillField.h"

/*adds new car to the cars tree.*/
Data setCarData() {
    Car* new_car;
    double licenseNum;
    char chassisNum[6];
    int manufactorYear;
    int onRoadSince;
    double priceFromSupplier;
    double currentPrice;
    int velocity;
    new_car = ALLOC(Car, 1);

    printf("please enter details for your new car:\n");

    /*setting user inputs to fields
     * checking input validation*/
    puts("please enter licence number (7 digits):");
    fillFieldDouble(&licenseNum, 7, 1);
    new_car->licenseNum = licenseNum;

    puts("please enter chassis number (5 digits): ");
    fillFieldStr(chassisNum, 5, 1, 1);
    strcpy(new_car->chassisNum, chassisNum);

    puts("please enter manufacturer name: ");
    new_car->manufacturer = fillFiledStrDynamic(2);

    puts("please enter model name: ");
    new_car->model = fillFiledStrDynamic(2);

    puts("please enter car's color: ");
    new_car->color = fillFiledStrDynamic(2);

    puts("please enter manufacturing year (4 digits): ");
    fillFieldInt(&manufactorYear, 4, 1,5);
    new_car->manufactorYear = manufactorYear;

    puts("please enter ascension year (4 digits): ");
    fillFieldInt(&onRoadSince, 4, 1,5);
    new_car->onRoadSince = onRoadSince;

    puts("please enter price from supplier (7 digits max): ");
    fillFieldDouble(&priceFromSupplier, 7, 0);
    new_car->priceFromSupplier = priceFromSupplier;

    puts("please enter current price (7 digits max): ");
    fillFieldDouble(&currentPrice, 7, 0);
    new_car->currentPrice = currentPrice;

    puts("please enter engine's velocity (4 digits): ");
    fillFieldInt(&velocity, 4, 1,1);
    new_car->velocity = velocity;

    return new_car;
}

int addNewCar(Tree tree){
    return addNewNode(tree);
}

/*free allocated memory*/
void freeCar(Data data){
    FREE(((Car*)(data))->manufacturer);
    FREE(((Car*)(data))->color);
    FREE(((Car*)(data))->model);
    FREE(data);
}

/*copying data to destination node.
 * allocating new memory for dynamic allocated data copying.*/
int carCopy(Node dest, Data source){
    Car* carData = ((Car*)dest->data);
    Car* carSource = ((Car*)source);

    carData->manufacturer = copyField(((Car*)source)->manufacturer); /*TODO*/
    ((Car*)(dest->data))->color = copyField(carSource->color); /*TODO*/
    ((Car*)(dest->data))->model = copyField(((Car*)source)->model);
    ((Car*)(dest->data))->licenseNum = ((Car*)source)->licenseNum;
    ((Car*)(dest->data))->manufactorYear = ((Car*)source)->manufactorYear;
    ((Car*)(dest->data))->velocity = ((Car*)source)->velocity;
    ((Car*)(dest->data))->onRoadSince = ((Car*)source)->onRoadSince;
    ((Car*)(dest->data))->currentPrice = ((Car*)source)->currentPrice;
    ((Car*)(dest->data))->priceFromSupplier = ((Car*)source)->priceFromSupplier;
    strcpy(((Car*)(dest->data))->chassisNum, ((Car*)source)->chassisNum);

    return 1;
}

double carCompare(void * license1,void * license2){
    return *(double*)license1-*(double*)license2;
}

/*allocating new binary search tree pointer. sets values to 0.*/
Tree createCarTree(){
    return treeCreate(carCopy, freeCar, carCompare, setCarData);
}

int deleteCar(Tree tree){
    double* userInput = 0;

    /*gets input from user*/
    puts("please enter license num for the car you wish to delete:");
    fillFieldDouble(userInput, 7, 1);

    deleteNode(tree, tree->root, userInput);
    return 1;
}

int deleteAllCars(Tree tree){
    freeAllNodes(tree, tree->root);
    tree->size = 0;
    return 1;
}


/*returns the number of cars in the list with a given capacity*/
/*cap parameter always starts as 0.*/
int carNumberWithGivenCapacity(Node root, int cap){
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
    if(((Car*)root->data)->velocity == userInput){
        res++;
    }

    /*sums results of children*/
    res += carNumberWithGivenCapacity(root->left, userInput);
    res += carNumberWithGivenCapacity(root->right, userInput);
    return res;
}









