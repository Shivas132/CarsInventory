#ifndef CAR_H
#define CAR_H
#include "GenericDataStructures.h"

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

/*using generic function treeCreate to initialize new car tree.*/
Tree createCarTree();

/*using generic function addNewNode to add new car to the cars tree*/
int addNewCar(Tree tree);

/*using generic function deleteNode to remove car node from the tree.*/
void deleteCar(Tree tree);

/*using generic function deleteAllNodes to remove all cars from the tree anf free all allocating memory.*/
int deleteAllCars(Tree tree);

/*returns the number of cars in the list with a given capacity*/
/*cap parameter always starts as 0.*/
int carNumberWithGivenCapacity(Node root, int cap);

/*print all the fields of given car*/
void printCarData(Data data);

#endif
