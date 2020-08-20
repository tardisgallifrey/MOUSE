//MOUSE Programming Language Interpreter
//by Dave Vest
//as described by Peter Grogono in
//MOUSE: A programming language for microcomputers
//(c)1983
//
//Credit for the stack functions go to TryToProgram web site
//http://www.trytoprogram.com/c-programming/stack-in-c/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

//Set max length of program array
#define MAXPROGLEN 1000

//declaring stack structure
struct stack
{
   int data;
   struct stack *ptr; //pointer type of stack
};

typedef struct stack Stack;
typedef Stack *stackPtr;

//function prototypes of different functions
void push(stackPtr *top, int x);                        //for pushing value in stack
int pop(stackPtr *top);                                 //for popping value out of stack
int checkEmpty(stackPtr top);                           //checking whether stack is empty

//function to convert ascii numbers to integers
int ctoi( char ch);


int main(int argc, char *argv[])                        //get mouse program file from command line
{
    
    FILE *filePointer;                                  //pointer to file
    char *is_it_mouse;                                  //check to see if file ends in .mouse
    char ch;
    char *filename = malloc(255 * sizeof(char));        //read character
    char *prog = malloc(MAXPROGLEN * sizeof(char));     //program array of characters
    int charpos = 0;                                    //character position in array
    int temp;
    stackPtr stackNewPtr = NULL;                        //declared pointer that points to the top of stack


    filename = argv[1];                                 //point filepointer to filename
    is_it_mouse = strstr(filename, ".mouse");           //see if filename contains .mouse

    if(argc != 2 || is_it_mouse == NULL){               //check to see if a file name is included and proper type
        printf("\nUsage: mouse hello.mouse\n");
        printf("     Also, make sure file ends in .mouse\n");
        exit(-1);
    }

    filePointer = fopen(filename, "r");  //open mouse file

    
    //open file attempt
    if (filePointer == NULL)
    {
        printf("File does not exist or is not able to open. \n");
    }
    else
    {
        //if good open, the read in file
        while ((ch = fgetc(filePointer)) != EOF)
        {
        
            if(ch == '~'){ 

              while((ch = fgetc(filePointer)) != '\n'){
                  continue;
              }
              charpos = charpos - 1;
            }

            prog[charpos] = ch;
            charpos++;
        }
        
        //As a final item, if the program read in is too long, STOP.
        if(strlen(prog) > MAXPROGLEN){

            printf("Your mouse program is too long.");
            exit(0);

        }
    }


    //main program interpreter loop
    //set character counter and stack pointer to 0
    charpos = 0;
    
    while(prog[charpos] != '$'){

      ch = prog[charpos];

      switch(ch){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                //Convert number digits into integer numbers
                //Do groups until they are complete.
                temp = 0;
                do{
                    temp = 10 * temp + ctoi(ch);
                    charpos++;
                    ch = prog[charpos];
                }while(isdigit(ch));
                push(&stackNewPtr, temp);  
                charpos -= 1;
                break;
            case '+':
                push(&stackNewPtr, pop(&stackNewPtr) + pop(&stackNewPtr) );
                break;
            case '-':
                temp = pop(&stackNewPtr);
                push(&stackNewPtr, pop(&stackNewPtr) - temp );
                break;
            case '*':
                push(&stackNewPtr, pop(&stackNewPtr) * pop(&stackNewPtr));
                break;
            case '/':
                temp = pop(&stackNewPtr);
                push(&stackNewPtr, pop(&stackNewPtr) / temp);
                break;
            case '%':
                temp = pop(&stackNewPtr);
                push(&stackNewPtr, pop(&stackNewPtr) % temp);
                break;
            case '!':
                printf("%d", pop(&stackNewPtr));
                break;
            default:
                break;

      }
      charpos++;

    }
    fclose(filePointer);
    
    return 0;
}

//convert number character to digit
int ctoi(char ch){

    int digit = ch - '0';
    if(digit >= 0 && digit <= 9){
        return digit;
    }
}

//function for pushing value into the top of stack
void push( stackPtr *top, int x )
{
    stackPtr nodePtr;

    //allocating memory
    nodePtr = malloc(sizeof(Stack));

    //pushing value at the top of stack only if there is space
    if(nodePtr != NULL)
    {
       nodePtr -> data = x;
       nodePtr -> ptr = *top;
       *top = nodePtr;
    }

    else
       printf("\nERROR !!! (Not enough space)");
   }

//popping value out of the stack
int pop(stackPtr *top)
{
   int pValue; //variable for value at the top
   stackPtr tempPtr; //temporary pointer

   tempPtr = *top;
   pValue = (*top) -> data;
   *top = (*top) -> ptr;
   free(tempPtr); //free temporary pointer value
   return pValue;
}

int checkEmpty(stackPtr top)
{
   return top == NULL;
}


