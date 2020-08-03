#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZ 128 
#define RSIZ 10 

int main(int argc, char *argv[]) 
{
    char line[RSIZ][LSIZ];
    FILE *fptr = NULL; 
    int i = 0;
    int tot = 0;

    fptr = fopen(argv[1], "r");
    while(fgets(line[i], LSIZ, fptr)) 
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }

    tot = i;
	printf("\n The content of the file %s  are : \n",argv[1]);    
    for(i = 0; i < tot; ++i)
    {
        printf(" %s\n", line[i]);
    }
    printf("\n");
    return 0;
}
