#include <stdio.h>

#define MAX_CHARS       8192
#define MAX_WORDS_HIST  1024
#define MAX_LINE        256

char chars[MAX_CHARS];
int idx_alloc_chars;

/*
 * Aloca espaço para novas palavras.
 */
char * alloc_chars(int nchars){
    if(nchars + idx_alloc_chars > MAX_CHARS){
        return NULL;
    }
    char * p = chars + idx_alloc_chars;
    idx_alloc_chars += nchars;
    return p;
}

typedef struct {
    char* word;
    int count;
} wordHist, *PWordHist;

wordHist words[MAX_WORDS_HIST];
int idx_alloc_words;

void process_file_input(FILE* fin){
    char line[MAX_LINE];
    char token;

    while(fgets(line, MAX_LINE, fin) != NULL){
        const char * delims = " \n\t.!?:;";
        char * pw = strtok(line, delims);
        while(pw != NULL){
            pw = strtok(NULL, delims);
        }
    }
}

void words_histogram(FILE* fin, FILE* fout){
    process_file_input(fin);

    process_collection();
}

int main(){
    words_histogram(stdin, stdout);
    return 0;
}