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

size_t string_split(char * text, char * separators, char ** words, size_t words_size){
    /**
     *  Gets a string, breaks it to a series of tokens using [separators] as the delimeter 
     *  and stores the resulting string in an array.
     *  If no string is given, it uses the string given in the last function call.
     * 
     *  Args:
     *      char * text: Original string.
     *      char * separators: Delimiters.
     *      char ** words:  Array to store tokens
     *      size_t words_size: Size of the array
     * 
     *  Return:
     *      size_t: Number of strings in [words]
     * 
     */
    unsigned word_count;
    if(text != NULL)
        token = strtok(text, separators);
    
    for(word_count = 0; (word_count < words_size) && (token != NULL); word_count++){
        words[word_count] = token;
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
