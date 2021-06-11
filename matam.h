#ifndef MATAM_H
#define MATAM_H

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

void *checked_malloc(unsigned int);/*malloc with check if succeed.*/
void checked_free(void *);/*check if free scceed*/
void check_for_exit();/*check if all allocations free*/

#define ALLOC(typ,no) ((typ *) checked_malloc(sizeof(typ)*(no)))
#define FREE(ptr) checked_free(ptr)

#endif
