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
    /**
     * Checks if [min] and [sec] are valid and writes them in [datetime] if so.
     * 
     * Args:
     *      int min: Minute.
     *      int sec: Second.
     *      struct * tm datetime: Struct to write hour in.
     * 
     * Return:
     *      BOOL: Returns True if [min] and [sec] are valid, otherwise returns False.
     * 
     */
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
    /**
     * Checks if [hour] is a valid hour and writes it in [datetime] if so.
     * 
     * Args:
     *      int hour: Hour.
     *      struct * tm datetime: Struct to write hour in.
     * 
     * Return:
     *      BOOL: Returns True if [day] is valid, otherwise returns False.
     * 
     */
    if((hour >= MIN_VALID_HOUR) && (hour <= MAX_VALID_HOUR)){
        datetime->tm_hour = hour;
        return True;
    }
    return False;
}

BOOL time_is_valid(char *str, struct tm *tm){
    /**
     * Checks if [str] is a valid time in the "HH:mm:ss" format.
     * 
     * Args:
     *      char * str: Time.
     *      struct * tm: Struct to write time on.
     * 
     * Return:
     *      BOOL: Returns True if [str] is valid and in the "HH:mm:ss" format, otherwise returns False. 
     * 
     */
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
    /**
     * Checks if [year] is a leap year.
     * 
     * Args:
     *      int year: Year.
     * 
     * Return:
     *      BOOL: Return True if [year] is a leap year, otherwise returns False.
     * 
     */
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return True;
    return False;
}

BOOL day_is_valid(int day, struct tm *datetime){
    /**
     * Checks if [day] is a valid day and writes it in [datetime] if so.
     * 
     * Args:
     *      int month: Day.
     *      struct * tm datetime: Struct to write day in.
     * 
     * Return:
     *      BOOL: Returns True if [day] is valid, otherwise returns False.
     * 
     */
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

BOOL month_is_valid(int month, struct tm * datetime){
    /**
     * Checks if [month] is a valid month and writes it in [datetime] if so.
     * 
     * Args:
     *      int month: Month.
     *      struct * tm datetime: Struct to write month in.
     * 
     * Return:
     *      BOOL: Returns True if [month] is valid, otherwise returns False.
     * 
     */
    if((month >= MIN_VALID_MONTH) && (month <= MAX_VALID_MONTH)){
        datetime->tm_mon = (month-1);
        //tm_mon admits values from 0(January) to 11(December).
        return True;
    }
    return False;
}

BOOL year_is_valid(int year, struct tm * datetime){
    /**
     * Checks if [year] is a valid year and writes how many years have passed through since 1900 in [datetime] if so.
     * 
     * Args:
     *      int year: Year.
     *      struct tm * datetime: Struct to write year on.
     * 
     * Return:
     *      BOOL: Returns True if [year] is valid, otherwise returns False.
     * 
     */
    if((year >= MIN_VALID_YEAR) && (year <= MAX_VALID_YEAR)){
        datetime->tm_year = (year - MIN_VALID_YEAR);
        return True;
    }
    return False;
}

BOOL date_is_valid(char * str, struct tm * tm){
    /**
     * Checks if [str] is a valid date in the "dd-MM-yy" format.
     * 
     * Args:
     *      char * str: Date.
     *      struct * tm: Struct to write data on.
     * 
     * Return:
     *      BOOL: Returns True if [str] is valid and in the "dd-MM-yy" format, otherwise returns False. 
     * 
     */
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

int string_to_time(const char * string, struct tm * tm){
    /**
     * Converts [string] information to a tm struct, if it is in the "dd-MM-yyyy HH:mm:ss" format.
     * 
     * Args:
     *      const char * string: String with date and time.
     *      struct tm * tm: Struct to write date and time in.
     * 
     * Return:
     *      int: Returns 1 if [string] is in the "dd-MM-yyyy HH:mm:ss" format, otherwise returns 0.
     * 
     */
    char delim[] = " ";
    char txt[MAX_DATA_SIZE]; 
	strcpy(txt, string);
    // a copy of [string] has to be created as the strtok() function changes the string given to it.
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