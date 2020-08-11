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
    char *is_it_mouse;                                  //check to see if file ends in .mouse
    char ch;       
    char *filename = malloc(255 * sizeof(char));        //read character
    char *prog = malloc(MAXPROGLEN * sizeof(char));     //program array of characters
    int charpos = 0;                                    //character position in array


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
        
            prog[charpos] = ch;
            charpos++;

        }
        prog[charpos + 1] = '\0';           //append string null character
        printf("%s \n", prog);

    }

    
    fclose(filePointer);

    return 0;
}