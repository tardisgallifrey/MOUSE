#include <stdio.h>
#include <stdlib.h>

int ctoi(char ch);

int main(){

char hold;
int temp;

hold = getchar();

switch(hold){
    case '3':
        temp = ctoi(hold);
        printf("%d\n", temp);
        break;
    default:
        break;
}


}




//convert number character to digit
int ctoi(char ch){

    int digit = ch - '0';
    if(digit >= 0 && digit <= 9){
        return digit;
    }
}
