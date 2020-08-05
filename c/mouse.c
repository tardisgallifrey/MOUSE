//MOUSE Programming Language Interpreter
//by Dave Vest
//as described by Peter Grogono in
//MOUSE: A programming language for microcomputers
//(c)1983

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//Set max length of program array
#define MAXPROGLEN 1000

int main(int argc, char *argv[])                        //get mouse program file from command line
{
    
    FILE *filePointer;                                  //pointer to file
    char *is_it_mouse;
    char ch;       
    char *filename = malloc(100 * sizeof(char));        //read character
    char *prog = malloc(MAXPROGLEN * sizeof(char));     //program array of characters
    int charpos = 0;                                    //character position in array


    filename = argv[1];
    is_it_mouse = strstr(filename, ".mouse");

    if(argc != 2 || is_it_mouse == NULL){                                      //check to see if a file name is included
        printf("\nUsage: mouse hello.mouse\n");
        printf("     Also, make sure file ends in .mouse\n");
        exit(-1);
    }

    filePointer = fopen(filename, "r");  //open mouse file

    
    if (filePointer == NULL)
    {
        printf("File does not exist or is not able to open. \n");
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

    
    fclose(filePointer);

    return 0;
}