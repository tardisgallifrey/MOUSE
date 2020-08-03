//MOUSE Programming Language Interpreter
//by Dave Vest
//as described by Peter Grogono in
//MOUSE: A programming language for microcomputers
//(c)1983

#include <stdio.h>
#include <stdlib.h>

//Set max length of program array
#define MAXPROGLEN 1000

int main(int argc, char *argv[])        //get mouse program file from command line
{
    
    FILE *filePointer;                  //pointer to file
    char ch;                            //read character
    char prog[MAXPROGLEN];              //program array of characters
    int charpos = 0;                    //character position in array

    if(argc != 2){                      //check to see if a file name is included
        printf("\nUsage: mouse hello.mouse\n");
    }

    filePointer = fopen(argv[1], "r");  //open mouse file

    //
    if (filePointer == NULL)
    {
        printf("File is not available \n");
    }
    else
    {
        //4
        while ((ch = fgetc(filePointer)) != EOF)
        {
        
            prog[charpos] = ch;
            charpos++;

        }
        prog[charpos + 1] = '\0';
        printf("%s \n", prog);

    }

    //5
    fclose(filePointer);

    return 0;
}