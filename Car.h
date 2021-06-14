#ifndef CAR_H
#define CAR_H
#include "BinarySearchTree.h"

typedef struct{
    double licenseNum;
    char chassisNum[6];
    char* manufacturer;
    char* model;
    char* color;
    int manufactorYear;
    int onRoadSince;
    double priceFromSupplier;
    double currentPrice;
    int velocity;
}Car;

typedef struct carNode_t{
    Car car;
    struct carNode_t* left;
    struct carNode_t* right;
}carNode;

typedef struct {
    carNode* root;
    int size;
} carBST;




/*creates empty carNode*/
Tree createCarTree();

/*adds new car to the cars list[index]. return 1 if succeed, 0 if failed*/
Data setCarData();

int addNewCar(Tree tree);

/*help function to call in setCarData*/
carNode* appendCarToTree(carNode* root, Car new_car, carBST* carTree);

/*gets license number of a car and delete it from the list. returns 1 if succeed, 0 if failed.*/
carNode* deleteCar(carNode* tree, double license,carBST* bst);

/*deletes all the cars from the list. returns 1 if succeed, 0 if failed.*/
int deleteAllCars(carBST* tree);

/*returns the number of cars from the list with a given capacity*/
int carNumberWithGivenCapacity(carNode* root, int cap);

double carCompare(void * license1,void * license2);
int carCopy(Node dest, Data source);
void freeCar(Data data);


#endif
