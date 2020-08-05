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

int main(int argc, char *argv[])                        //get mouse program file from command line
{
    ifstream filePointer;
    char ch;                                        //read character
    char *is_it_mouse;
    char *filename = (char*)malloc(100);
    char *prog = (char*)malloc(MAXPROGLEN);         //program array of characters
    int charpos = 0;                                //character position in array
    string line;

    filename = argv[1];
    is_it_mouse = strstr(filename, ".mouse");

    if(argc != 2 || is_it_mouse == NULL){                                      //check to see if a file name is included
        cout << "\nUsage: mouse hello.mouse" << endl;
        cout << "     Also, be sure file ends in .mouse" << endl;
        exit(-1);
    }

    filePointer.open( filename );        //open mouse file

    //
    if (filePointer.bad())
    {
        cout << "File cannot be opened, or does not exist." << endl;
    }
    else
    {
        //4
        while (!filePointer.eof())
        {
        
            filePointer.get(prog[charpos]);
            charpos++;

        }
        prog[charpos + 1] = '\0';
        cout << prog << endl;

    }
    filePointer.close();

    return 0;
}