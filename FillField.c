#include "FillField.h"

/*checks string input and fills a field.
 * param:
 * str: string to check and fill.
 * size: number of characters, without '\0'.
 * charType: 1 for integers, 2 for alphabet, 3 for date.
 * fixed: 1 for fixed size, 0 for maximum limitation.
 * */
int fillFieldStr(char* str, int size, int charType, int fixed) {
    char userInput[24];/*larger than the longest string required*/
    int charCheck, tooLong, tooShort;
    while (1){
        fgets(userInput, 24, stdin);
        charCheck = isStrValid(userInput , charType);
        tooLong = isTooLong(userInput, size);
        if (fixed == 1){
            tooShort = isLongEnough(userInput, size);
        }
        else {
            tooShort = isLongEnough(userInput,1);
        }
        if((charCheck == 1) &&(tooLong == 1)&&(tooShort==1)) {
            strcpy(str, userInput);
            str[strlen(str)-1]='\0';
            return 1;
            }
        if (tooShort == 0){
            puts("too short please try again");

        }
        if (charCheck ==0){
            puts("wrong type or format, please try again");

        }
        if(tooLong == 0) {
            puts("too long please try again");
            fflush(stdin);
            }
        }
    }

char* fillFiledStrDynamic(int charType){
    /*works similar to fillFieldStr, but without checking if input is too long.*/
    char userInput[250];
    char* ptr;
    int charCheck, tooShort;
    while (1){
        fgets(userInput, 250, stdin);
        charCheck = isStrValid(userInput , charType);
        tooShort = isLongEnough(userInput,1);
        if((charCheck == 1)&&(tooShort==1)) {
            /*allocating new string and checks validations*/
            ptr = ALLOC(char, strlen(userInput)+1);
            strcpy(ptr, userInput);
            ptr[strlen(ptr)-1]='\0';
            return ptr;
        }
        if (tooShort == 0){
            puts("too short please try again");

        }
        if (charCheck ==0){
            puts("wrong type or format, please try again");
        }
    }
}

/* using fillFieldStr function to get a numeric input from the user
 and cast the output into an int*/
int fillFieldInt(int * field, int size,int fixed,int charType){
    char userInput[24];
    fillFieldStr(userInput, size, charType, fixed);
    *field = atoi(userInput);
    return 1;
}
/* using fillFieldStr function to get a numeric input from the user and cast the output
 * into a double*/
int fillFieldDouble(double * field, int size,int fixed){
    char userInput[24];
    fillFieldStr(userInput, size, 1,fixed);
    *field = atof(userInput);
    return 1;
}

/*gets source string, returns new dynamic allocated string*/
char* copyField(char* source){
    char * dest;
    dest = ALLOC(char, strlen(source)+1);
    strcpy(dest,source);
    return dest;
}

