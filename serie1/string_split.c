#include <stdio.h>
#include <string.h>

char * token;

size_t get_addresses(char *separators, char *words[], size_t words_size){
    size_t local_count;
    for(local_count = 0; local_count < words_size; local_count++){
        /*
         * TODO: Find out if another array of pointers should be defined to store the addresses of the words
         * obtained after the first call.
         */
        words[local_count] = token;
        printf("[Pointer] words[%ld] = %p\n", local_count, words[local_count]);
        printf("[Value] words[%ld] = %s\n", local_count, words[local_count]);
        token = strtok(NULL, separators);
        if(!token){
            return ++local_count;
        }
    }
    return local_count;
}

size_t string_split(char *text, char *separators, char *words[], size_t words_size){
    size_t word_count;
    if(text){
        token = strtok(text, separators);
    }
    word_count = get_addresses(separators, words, words_size);
    if(word_count == words_size){
        word_count += string_split(NULL, separators, words, words_size);
    }
    return word_count;
}

int main(){
    char text[] = "Lorem\tipsum\ndolor\tsit\namet";
    char delim[] = " \n\t";
    char* words[2];
    size_t count = (size_t) (sizeof(words) / sizeof(words[0]));
    printf("\nword count: %ld\n", string_split(text, delim, words, count));
    return 0;
}