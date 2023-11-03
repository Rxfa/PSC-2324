#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>

typedef unsigned int BOOL;
#define False 0
#define True !False

#define MAX_LENGTH 1024

BOOL row_is_valid(char * line, char * pattern, int column, int case_sensitive){
    /**
     * Checks if [column]nth column in a row of a CSV file matches [pattern].
     * [case_sensitive] specifies if we want a case-sensitive match or not.
     * 
     * Args:
     *      char * line: Row of CSV file.
     *      char * pattern: Value we are searching for.
     *      int column: Number of the column to match with [pattern].
     *      int case_sensitive: (Acts as a flag) If set, a case-sensitive match is done.
     * 
     * Return:
     *      int: 1 if there is a match, otherwise 0 is returned.
     * 
     */
    char delim[] = ",";
    char * line_copy = malloc(MAX_LENGTH);
    strcpy(line_copy, line); 
    // a copy of [line] has to be created as the strtok() function changes the string given to it
    char * token = strtok(line_copy, delim);
    for(int i = 1; i < column; i++){
        token = strtok(NULL, delim);
    }
    if(
        ((case_sensitive != 0) && (strcmp(token, pattern) == 0)) ||
        ((case_sensitive == 0) && (strcasecmp(token, pattern) == 0))
    )
        return True;
    return False;
}

void csv_filter(FILE * input, FILE * output, char * pattern, int column, int case_sensitive){
    /**
     * Reads a CSV file and writes in another CSV file, 
     * the rows of the input file where the value of the [column]nth column matches [pattern].
     * [case_sensitive] specifies if we want a case-sensitive match or not.
     * 
     * Args:
     *      FILE * input: Input file.
     *      FILE * output: Output file.
     *      char * pattern: Value to match.
     *      int column: Number of the column to match [pattern] with.
     *      int case_sensitive: (Acts as a flag) If set, a case-sensitive match is done.
     * 
     * Return:
     *      void: writes matching rows from [input] to [output].
     */
    char buffer[MAX_LENGTH];
    while(fgets(buffer, MAX_LENGTH, input) != NULL){
        if(row_is_valid(buffer, pattern, column, case_sensitive) == True)
            fprintf(output, "%s", buffer);
    }

}


int main(int argc, char * argv[]){
    /**
     * Main function
     */
    FILE * fpin = stdin;
    FILE * fpout = stdout;
    char * PATH = getenv("CSV_FILTER_PATH");
    char * fin = NULL;
    char * fout = NULL;
    char * pattern = NULL;
    int column = 0;
    int opt = 0;
    int errflg = 0;
    int case_sensitive = 0;

    while((opt = getopt(argc, argv, ":ci:o:")) != -1){
        switch(opt){
            case 'c':
                case_sensitive++;
                break;
            case 'o':
                fout = optarg;
                break;
            case 'i':
                fin = optarg;
                if(PATH){
                    strcat(PATH, "/");
                    strcat(PATH, fin); 
                }
                break;
            case '?':
                if(optopt == 'i'){
                    printf("[Error] Option -%c requires an argument\n", optopt);
                } else if(optopt == 'o') {
                    printf("[Error] Option -%c requires an argument\n", optopt);
                    printf("[Error] Unrecognized option: %c\n", optopt);
                } else {}
                errflg++;
                break;
            case ':':
                printf("[Error] Missing arg for %c\n", optopt);
                errflg++;
                break;
        }
    }

    if(errflg)
        return 1;

    if(fin){
        if(PATH != NULL && access(PATH, R_OK) == 0){ // File exists and we have read permissions
            fpin = fopen(PATH, "r"); 
        } else {
            fpin = fopen(fin, "r");
        }
        if(fpin == NULL){
            printf("[Error] Opening input file: \"%s\"\n", fin);
            return 1;
        }
    }

    if(fout){
        fpout = fopen(fout, "w");
        if(fpout == NULL){
            printf("[Error] Creating output file: \"%s\"\n", fout);
            return 1;
        }
    }

    if(((argc - optind) != 2) || (isdigit(*argv[optind]) == 0)){
        printf("[Usage] %s -i <FILE:input_file> -o <FILE:output_file> <INT:Column> <STR:pattern>\n", argv[0]);
        printf("Flags:\n");
        printf("\t-c\tCase-sensitive search\n\n");
        return 1;
    }

    column = atoi(argv[optind++]);
    pattern = argv[optind++];

    csv_filter(fpin, fpout, pattern, column, case_sensitive);

    if(fin)
        fclose(fpin);

    if(fout)
        fclose(fpout);

    return 0;
}