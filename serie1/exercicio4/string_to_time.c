#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned int BOOL;
#define False 0
#define True !False

#define MIN_VALID_YEAR 1900 // Should be the minimum according to the docs.
#define MAX_VALID_YEAR 2023

#define MIN_VALID_MONTH 1
#define MAX_VALID_MONTH 12

#define MIN_VALID_DAY 1

#define MIN_VALID_HOUR 0
#define MAX_VALID_HOUR 23

#define MIN_VALID_MIN 0
#define MAX_VALID_MIN 59

#define FEBRUARY 1

#define MAX_DATA_SIZE 20

BOOL validate_min_and_sec(int min, int sec, struct tm *datetime){
    if(
        (min >= MIN_VALID_MIN) && (min <= MAX_VALID_MIN) && 
        (sec >= MIN_VALID_MIN) && (sec <= MAX_VALID_MIN)
    ){
        datetime->tm_min = min;
        datetime->tm_sec = sec;
        return True;
    }
    return False;
}

BOOL validate_hour(int hour, struct tm *datetime){
    if((hour >= MIN_VALID_HOUR) && (hour <= MAX_VALID_HOUR)){
        datetime->tm_hour = hour;
        return True;
    }
    return False;
}

BOOL time_is_valid(char *str, struct tm *tm){
    char delim[] = ":";
    char *hour = strtok(str, delim);
    char *min = strtok(NULL, delim);
    char *sec = strtok(NULL, delim); 
    if(
        (hour != NULL) &&
        (min != NULL) &&
        (sec != NULL) &&
        (validate_hour(atoi(hour), tm) == True) &&
        (validate_min_and_sec(atoi(min), atoi(sec), tm) == True)
    )
        return True;
    return False; 
}

BOOL is_leap_year(int year){
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return True;
    return False;
}

BOOL day_is_valid(int day, struct tm *datetime){
    int month = datetime->tm_mon;
    int year = datetime->tm_year;
    
    int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if((month == FEBRUARY) && (is_leap_year(year) == True))
        months[FEBRUARY] = 29;
    if((day >= MIN_VALID_DAY) && (day <= months[month])){
        datetime->tm_mday = day;
        return True;
    }
    return False;
}

BOOL month_is_valid(int month, struct tm *datetime){
    if((month >= MIN_VALID_MONTH) && (month <= MAX_VALID_MONTH)){
        datetime->tm_mon = (month-1);
        return True;
    }
    return False;
}

BOOL year_is_valid(int year, struct tm *datetime){
    if((year >= MIN_VALID_YEAR) && (year <= MAX_VALID_YEAR)){
        datetime->tm_year = (year - MIN_VALID_YEAR);
        return True;
    }
    return False;
}

BOOL date_is_valid(char *str, struct tm *tm){
    char delim[] = "-";
    char *day = strtok(str, delim);
    char *month = strtok(NULL, delim);
    char *year = strtok(NULL, delim);

    if( 
        (year != NULL) &&
        (month != NULL) && 
        (day != NULL) &&
        (year_is_valid(atoi(year), tm) == True) &&
        (month_is_valid(atoi(month), tm) == True) &&
        (day_is_valid(atoi(day), tm) == True)
    )
        return True;
    return False; 
}

int string_to_time(const char *string, struct tm *tm){
    // Since we have a const char pointer and strtok() writes on its first argument, 
    // we have to create writable copy of the [string] to tokenize.
    //
    // So we use the malloc() function that will return a pointer to a memory block of atleast 20 bytes,
    // which is the amount of memory occupied by a string with the valid date, 
    // according to our required format.
    //
    // Then we copy the content of [string] to our newly created pointer using the strcpy() function.
    char delim[] = " ";
    char *txt = malloc(MAX_DATA_SIZE); 
	strcpy(txt, string);
    char *date = strtok(txt, delim);
    char *time = strtok(NULL, delim); 
    if( 
        (date != NULL) && 
        (time != NULL) &&
        (date_is_valid(date, tm) == True) &&
        (time_is_valid(time, tm) == True)
    )
        return 1;
    return 0;
}

/*
int main(){
    char date[] = "11-9-2023 13:43";
    struct tm a;
    if(string_to_time(date, &a) == True){
        printf("[RESULT] - Valid\n");
        return 1;
    }
    printf("[RESULT] - False\n");
    return 0;
}
*/