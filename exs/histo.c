#include <stdio.h>

int arr[10];
char input;


void main() {
  while((input = getchar()), input != EOF){
    if(isDigit(input)){
        input -= '0';
        arr[input]++;
    } else {
        continue;
    }
  }

  for(int i = 0; i < 10; i++){
    printf("%D: ", arr[input]);
    for(int j = 0; j < arr[i]; j++){
        printf("*");
    }
    printf("\n");
  }
}

int isDigit(int digit){
    if(digit > '0' && digit < '9')
        return 1;
    else
        return 0;
};

