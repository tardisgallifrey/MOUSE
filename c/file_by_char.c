#include <stdio.h>
#include <stdlib.h>

#define MAXPROGLEN 1000

int main(int argc, char *argv[])
{
    //1
    FILE *filePointer;
    char ch;
    char prog[MAXPROGLEN];
    int charpos = 0;

    filePointer = fopen(argv[1], "r");

    //3
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