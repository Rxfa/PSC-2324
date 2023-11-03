#include <stdio.h>

/* Count the number of words in a file.
 * Use Ctrl^D to produce EOF from command line.
 * Use ./words < file to redirect stdin to file.
 */
int main() {
    int nextChar;   // char readed 
    int count = 0;  // words counter
    int inWord = 0; // current state
    while (( nextChar = getchar() ) != EOF) {
        if (nextChar == '\n'|| nextChar == ' ')
            inWord = 0;
        else
            if (! inWord) {
                inWord = 1;
                count += 1;
            }
    }
    printf("Words count=%d\n", count);
    return 0;
}
