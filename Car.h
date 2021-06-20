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

/*creates empty carNode*/
Tree createCarTree();

/*adds new car to the cars list[index]. return 1 if succeed, 0 if failed*/
Data setCarData();

int addNewCar(Tree tree);

/*gets license number of a car and delete it from the list. returns 1 if succeed, 0 if failed.*/
void deleteCar(Tree tree);

/*deletes all the cars from the list. returns 1 if succeed, 0 if failed.*/
int deleteAllCars(Tree tree);

/*returns the number of cars from the list with a given capacity*/
int carNumberWithGivenCapacity(Node root, int cap);

double carCompare(void * license1,void * license2);

int carCopy(Node dest, Data source);

void freeCar(Data data);

void printCarData(Data data);


#endif
