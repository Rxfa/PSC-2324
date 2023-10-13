#include <stdio.h>
#include <string.h>

char * token;
/**
 *  Has to be a global variable so we can still obtain text in case string_split() is called with the
 *  text parameter as NULL.
 *  If we try to define it as a local variable, the for loop in string_split() will
 *  try to assign an uninitialized pointer as words[word_count]'s value, giving us a SegFault error.
 * 
 */

size_t string_split(char *text, char *separators, char *words[], size_t words_size){
    size_t word_count;
    if(text != NULL)
        token = strtok(text, separators);
    
    for(word_count = 0; (word_count < words_size) && (token != NULL); word_count++){
        words[word_count] = token;
        //printf("[Pointer] words[%ld] = %p\n", word_count, words[word_count]);
        //printf("[Value] words[%ld] = %s\n", word_count, words[word_count]);
        token = strtok(NULL, separators);
    }
    return word_count;
}


/*
int main(){
    char text[] = "aaa bbb ccc ddd";
    char delim[] = " \n\t";
    int array_size = 4;
    char* words[array_size];
    size_t count = (size_t) (sizeof(words) / sizeof(words[0]));
    printf("\nword count: %ld\n", string_split(text, delim, words, count));
    return 0;
}
*/
