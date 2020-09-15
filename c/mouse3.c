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
#define STACKSIZE 20

//Define stack and pointer
int stack_num[STACKSIZE];
int stackpointer = -1;
int ctoi(char ch);
int push(int val);
int pop();

int main(int argc, char *argv[])                        //get mouse program file from command line
{
    
    FILE *filePointer;                                  //pointer to file
    char *is_it_mouse;                                  //check to see if file ends in .mouse
    char ch;
    char *filename = malloc(255 * sizeof(char));        //read character
    char *prog = malloc(MAXPROGLEN * sizeof(char));     //program array of characters
    char data_strings[26][255];
    int *data_nums = malloc( 26 * sizeof(int));
    char *buffer = malloc(MAXPROGLEN * sizeof(char));
    int charpos = 0;                                    //character position in array
    int temp;
    int index;

    //Initialize string variable array to empty strings
    for(int i = 0; i < 26; i++)
    {
        data_strings[i][0]='\0';
    }
    

    if(argc != 2){               //check to see if a file name is included and proper type
        printf("\nUsage: mouse hello.mouse\n");
        printf("     Also, make sure file ends in .mouse\n");
        exit(-1);
    }
    else
    {
        filename = argv[1];                                 //point filepointer to filename
        is_it_mouse = strstr(filename, ".mouse");           //see if filename contains .mouse
        if(!is_it_mouse)
        {
            printf("This isn't a mouse program.\n");
            exit(-1);
        }
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
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                temp = ch - 'A';
                charpos++;
                ch = prog[charpos];
                if(ch == ':')
                {
                    data_nums[temp]=pop();
                }
                if(ch == '.')
                {
                    push(data_nums[temp]);
                }
                break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                temp = ch - 'a';
                prog++;
                ch = prog[charpos];
                index = 0;
                if( ch == ':')
                {
                    charpos += 2;
                    ch = prog[charpos];
                    while(ch != '"')
                    {
                        if(ch == '!')
                        {
                            buffer[index]='\n';
                        }
                        else
                        {
                            buffer[index]=ch;
                        }
                        index++;
                        charpos++;
                        ch = prog[charpos];
                    }
                    buffer[index+1]='\0';
                    strcpy(data_strings[temp], buffer);
                }
                if(ch == '.')
                {
                    printf("%s", data_strings[temp]);
                }

                for(index=0;index < MAXPROGLEN;index++)
                {
                    buffer[index]='\0';
                }
                break;
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
                push(temp);  
                charpos -= 1;
                break;
            case '+':
                push(pop() + pop() );
                break;
            case '-':
                temp = pop();
                push(pop() - temp );
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                temp = pop();
                push(pop() / temp);
                break;
            case '%':
                temp = pop();
                push(pop() % temp);
                break;
            case '?':
                scanf("%d", &temp);
                push(temp);
                break;
            case '!':
                printf("%d", pop());
                break;
            case '"':
                charpos++;
                ch = prog[charpos];
                index = 0;
                while(ch != '"')
                {
                    if(ch == '!')
                    {
                        buffer[index]='\n';
                    }
                    else
                    {
                        buffer[index]=ch;

                    }
                    index++;
                    charpos++;
                    ch = prog[charpos];
                }
                buffer[index+1]='\0';
                printf("%s", buffer);
                for(index=0;index < MAXPROGLEN;index++)
                {
                    buffer[index]='\0';
                }
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

//push a number onto the stack_num
int push(int val) 
{
   if(stackpointer >= STACKSIZE-1)
   {
        return 0;
   } 
   else 
   {
      stackpointer++;
      stack_num[stackpointer]=val;
      return 1;
   }
}

//pop a number off of the stack_num
int pop() 
{
    int n;
    if(stackpointer <= -1)
    {
        printf("Stack Underflow.  Quitting.");
        exit(-1);
    }
    else 
    {
       n = stack_num[stackpointer]; 
       stackpointer--;
       return n;
    }
}

