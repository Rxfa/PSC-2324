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

int row_is_valid(char * line, char * pattern, char * column, int case_sensitive){
    char delim[] = ",";
    char * line_copy = malloc(MAX_LENGTH);
    strcpy(line_copy, line);
    char * token = strtok(line_copy, delim);
    for(int i = 1; i < atoi(column); i++){
        token = strtok(NULL, delim);
    }
    if(
        (case_sensitive && (strcmp(token, pattern) == 0)) ||
        (!case_sensitive && (strcasecmp(token, pattern) == 0))
    )
        return 1;
    return 0;
}

void csv_filter(FILE * input, FILE * output, char * pattern, char * column, int case_sensitive){
    char buffer[MAX_LENGTH];
    while(fgets(buffer, MAX_LENGTH, input) != NULL){
        if(row_is_valid(buffer, pattern, column, case_sensitive))
            fprintf(output, "%s", buffer);
    }

}


int main(int argc, char * argv[]){
    char * PATH = getenv("CSV_FILTER_PATH");
    char * fin = NULL;
    char * fout = NULL;
    char * column = NULL;
    char * pattern = NULL;
    FILE * fpin = stdin;
    FILE * fpout = stdout;
    int opt, errflg = 0;
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
                    printf("Option -%c requires an argument.\n", optopt);
                } else if(optopt == 'o') {
                    printf("Option -%c requires an argument.\n", optopt);
                    printf("Unrecognized option: %c\n", optopt);
                } else {}
                errflg++;
                break;
            case ':':
                printf("Missing arg for %c\n", optopt);
                errflg++;
                break;
        }
    }

    if(errflg)
        return 1;

    if(fin){
        if(PATH && access(PATH, R_OK) == 0){ // File exists and we have read permissions
            fpin = fopen(PATH, "r"); 
        } else {
            fpin = fopen(fin, "r");
        }
        if(fpin == NULL){
            printf("Error opening input file: \"%s\"\n", fin);
            return 1;
        }
    }

    if(fout){
        fpout = fopen(fout, "w");
        if(fpout == NULL){
            printf("Error creating output file: \"%s\"\n", fout);
            return 1;
        }
    }

    if((argc - optind) != 2){
        //printf("[Error] too many arguments!\n");
        return 1;
    }

    column = argv[optind++];
    pattern = argv[optind++];

    csv_filter(fpin, fpout, pattern, column, case_sensitive);

    if(fin)
        fclose(fpin);

    if(fout)
        fclose(fpout);

    return 0;
}