//MOUSE Programming Language Interpreter
//by Dave Vest
//as described by Peter Grogono in
//MOUSE: A programming language for microcomputers
//(c)1983

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Set max length of program array
#define MAXPROGLEN 1000

int main(int argc, char *argv[])        //get mouse program file from command line
{
    ifstream filePointer;
    char ch;                            //read character
    char prog[MAXPROGLEN];              //program array of characters
    int charpos = 0;                    //character position in array
    string line;

    if(argc != 2){                      //check to see if a file name is included
        cout << "\nUsage: mouse hello.mouse" << endl;
    }

    filePointer.open( argv[1] );        //open mouse file

    //
    if (filePointer.bad())
    {
        cout << "File is not available" << endl;
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