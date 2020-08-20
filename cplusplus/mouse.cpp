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

int ctoi(char ch);

char readprog(int charpos, char *prog);

int backpos(int charpos);

void push(int *stackpointer, int *stack, int datum);

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
    int *stackpointer;
    string line;

    //Read filename from command line
    filename = argv[1];
    is_it_mouse = strstr(filename, ".mouse");

    //What to do if command line is deficient
    if(argc != 2 || is_it_mouse == NULL){                                      //check to see if a file name is included
        cout << "\nUsage: mouse hello.mouse" << endl;
        cout << "     Also, be sure file ends in .mouse" << endl;
        exit(-1);
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
    ch = readprog(charpos, prog);
    charpos++;



}


int ctoi(char ch){

    if(ch>='0' && ch<='9'){
        return ch - '0';
    }
    else
    {
        return -1;
    }
    
}

char readprog(int charpos, char *prog){

    char ch = prog[charpos];
    return ch;
}

int backpos(int charpos){

    return charpos -= 1;

}

void push(int *stackpointer, int *stack, int datum){

    *stackpointer++;
    stack[*stackpointer] = datum;

}

int pop(int *stackpointer, int *stack){

    int temp = stack[*stackpointer];
    return temp;
}
