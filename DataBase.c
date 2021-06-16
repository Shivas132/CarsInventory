#include "DataBase.h"
#include <stdio.h>

/*returns manufacturing year of a car by a given license number*/
int getCarYearByLicense(Node node , double license){
    Car* car;

    if(!node){
        return 0;
    }
    car = ((Car*)node->data);
    if(car->licenseNum == license){
        return car->manufactorYear;
    }
    if(car->licenseNum > license){
        return getCarYearByLicense(node->left , license);
    }
    return getCarYearByLicense(node->right , license);
}

/*returns number of clients who rented a car with a given manufacture year.*/
int clientNumberWithGivenCarYear(Node car_node, Node client_node, int year) {
    int counter = 0, userYearChoice;

    if((!car_node) || (!client_node)){
        return 0;
    }

    if(year == 0) {
        puts("please enter a year to check: ");
        fillFieldInt(&userYearChoice, 4, 1, 5);
    }
    else{
        userYearChoice = year;
    }

    if(getCarYearByLicense(car_node, ((Client*)client_node->data)->rentedCarLicense) == userYearChoice){
        counter++;
    }

    return counter + clientNumberWithGivenCarYear(car_node, client_node->left, userYearChoice) + clientNumberWithGivenCarYear(car_node, client_node->right, userYearChoice);
}




