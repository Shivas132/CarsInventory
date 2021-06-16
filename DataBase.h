#ifndef DB_H
#define DB_H
#include "Car.h"
#include "Client.h"
#include "Supplier.h"
#include "FillField.h"

/*returns the number of clients that rents a car with a given manufacturing year*/
int clientNumberWithGivenCarYear(Node car_node, Node client_node, int year);

#endif
