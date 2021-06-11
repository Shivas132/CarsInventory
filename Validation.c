#include "Validation.h"

/*checks if given string is in the right size
 * param charType:
 * 1: numeric characters.
 * 2: alphabet characters and space.
 * 3: check date format and values.
 * 4: check hour format and values*/
int isStrValid(char* str, int charType) {
    int i;
    switch (charType) {
        case 1:
            for (i = 0; i < strlen(str) - 1; i++) {
                if (str[i] < '0' || str[i] > '9') {
                    return 0;
                }
            }
            break;

        case 2:
            for (i = 0; i < strlen(str) - 1; i++) {
                if ((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z') && str[i] != ' ') {
                    return 0;
                }
            }
            break;

        case 3: /*check if date is in the right format*/
            if (isDateValid(str) != 1) {
                return 0;
            }
            break;
        case 4:
            if (isHourValid(str) != 1) {
                return 0;
            }
            break;

        case 5:
            if (isYearValid(str) != 1) {
                return 0;
            }
            break;
    }
            return 1;
}

    /*checks if given string is in a valid date format and values.*/
    int isDateValid(char *str) {
        int i;
        for (i = 0; i < strlen(str) - 1; i++) {
            if ((i == 1) || (i == 8) || (i == 9)) {
                if (str[i] < '0' || str[i] > '9') {
                    return 0;
                }
            }
            if (i == 2 || i == 5) {
                if (str[i] != '/') {
                    return 0;
                }
            }
        }
        if (str[0] < '0' || str[0] > '3') {
            return 0;
        }
        if (str[0] == '3') {
            if (str[1] != '0' && str[1] != '1') {
                return 0;
            }
        }

        if (str[3] == '0') {
            if ((str[4]) == '0') {
                return 0;
            }
        }
        else if (str[3]== '1'){
            if ((str[4]) < '0' || str[4]>'2') {
                return 0;
            }
        }
        else return 0;
        if (str[6] != '2') {
            return 0;
        }
        if (str[7] != '0') {
            return 0;
        }
        return 1;
    }

    /*checks if given string is in a valid hour format and values.*/
    int isHourValid(char *str) {
        if (str[0] == '0' || str[0] == '1') {
            if (str[1] < '0' || str[1] > '9') {
                return 0;
            }
        } else if (str[0] == '2') {
            if (str[1] > '3' || str[1] < 0) {
                return 0;
            }
        } else return 0;

        if (str[2] != ':') {
            return 0;
        }
        if (str[3] < '0' || str[3] > '5') {
            return 0;
        }
        if (str[4] < '0' || str[4] > '9') {
            return 0;
        }
        return 1;
    }

/*checks if given string is in a valid year format and values.
*between 1900-2999*/
int isYearValid(char* year ) {
    if (year[0]=='1'){
        if(year[1]!='9'){
            return 0;
        }
    }
    else if (year[0] != '2') {
        return 0;
    }
    return isStrValid(year, 1);
}


int isLongEnough(char* str, int size){
    return strlen(str) < size+1 ? 0 :1;
}

int isTooLong(char* str, int size){
    if (strlen(str)-1>size){
        return 0;
    }
    return 1;
}



