//MOUSE Programming Language Interpreter
//by Dave Vest
//as described by Peter Grogono in
//MOUSE: A programming language for microcomputers
//(c)1983

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

//Set max length of program array
#define MAXPROGLEN 1000
#define STACKSIZE 20



struct stack
{
   int data;
   struct stack *ptr; //pointer type of stack
};

typedef struct stack Stack;
typedef Stack *stackPtr;

char readprog(int charpos, char *prog);
void push( stackPtr *top, int x );
int pop(stackPtr *top);
int ctoi(char ch);


int main(int argc, char *argv[])                        //get mouse program file from command line
{

    //Variable Declarations
    ifstream filePointer;
    char ch;                                        //read character
    char *is_it_mouse;
    char *filename = (char*)malloc(100);
    char *prog = (char*)malloc(MAXPROGLEN);         //program array of characters
    int *stack = (int*)malloc(STACKSIZE);
    int charpos = 0;                                //character position in array
    int temp;
    stackPtr stackNewPtr = NULL;                    //declared pointer that points to the top of stack
    string line;

       //What to do if command line is deficient
    if(argc != 2){                                      //check to see if a file name is included
        cout << "\nUsage: mouse hello.mouse" << endl;
        cout << "     Also, be sure file ends in .mouse" << endl;
        exit(-1);
    }
    else 
    {
         //Read filename from command line
        filename = argv[1];
        is_it_mouse = strstr(filename, ".mouse");
        if(!is_it_mouse)
        {
            cout << "     You didn't use a file ending in .mouse"<<endl;
            exit(-1);
        }
    }

    //Open MOUSE file and get going on reading in from file
    filePointer.open( filename );        //open mouse file

    if (filePointer.bad())
    {
        cout << "File cannot be opened, or does not exist." << endl;
    }
    else
    {
        //Read in file.
        while (!filePointer.eof())
        {

            //Get a character
            filePointer.get(prog[charpos]);
	        
            //If character is tilde (comment), bypass and read another
            if(prog[charpos] == '~'){
              while(prog[charpos] != '\n'){
                filePointer.get(prog[charpos]);
              }
              //If we did the above, backspace pos to discard tilde
              charpos = charpos -1;
            }
            //Increment and begin again.
            charpos++;

        }
        //At the end, add string NULL
        prog[charpos + 1] = '\0';

    }
    //close file pointer
    filePointer.close();

    //*******Begin Interpretation of MOUSE Program********
    
    //Reset the program counter and get your first character
    charpos = 0;

    while(prog[charpos] != '$'){

      ch = readprog(charpos, prog);

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
                    ch = readprog(charpos, prog);
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
}


char readprog(int charpos, char *prog){

    char ch = prog[charpos];
    return ch;
}

int backpos(int charpos){

    return charpos -= 1;

}

//function for pushing value into the top of stack
void push( stackPtr *top, int x )
{
    stackPtr nodePtr;

    //allocating memory
    nodePtr = (stackPtr)malloc(sizeof(Stack));

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

//convert number character to digit
int ctoi(char ch){

    int digit = ch - '0';
    if(digit >= 0 && digit <= 9){
        return digit;
    }
}