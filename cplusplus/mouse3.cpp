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

//Define stack and pointer
int stack_num[STACKSIZE];
int stackpointer = -1;

char readprog(int charpos, char *prog);
int backpos(int charpos);
int ctoi(char ch);
int push(int val);
int pop();


int main(int argc, char *argv[])                        //get mouse program file from command line
{

    //Variable Declarations
    ifstream filePointer;
    char ch;                                            //read character
    char *is_it_mouse;
    char *filename = (char*)malloc(100);
    char *prog = (char*)malloc(MAXPROGLEN);             //program array of characters
    int charpos = 0;                                    //character position in array
    int temp;
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
    //cout << prog << endl;

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
                push(temp);  
                backpos(charpos);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                temp = pop();
                push( pop() - temp);
                break;
            case '*':
                push( pop() * pop() );
                break;
            case '/':
                temp = pop();
                push( pop() / temp);
                break;
            case '%':
                temp = pop();
                push( pop() % temp);
                break;
            case '!':
                cout << pop();
                break;
            case '?':
                cin >> temp;
                push(temp);
                break;
            case '"':
                charpos++;
                ch = readprog(charpos, prog);
                while(ch != '"')
                {
                    if(ch == '!')
                    {
                        cout << endl;
                    }
                    else
                    {
                        cout << ch;
                    }
                    charpos++;
                    ch = readprog(charpos, prog);
                }
                break;
            default:
                break;

      }
      charpos++;
    }
    cout << endl;
}


char readprog(int charpos, char *prog){

    char ch = prog[charpos];
    return ch;
}

int backpos(int charpos){

    return charpos -= 1;

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
        cout << "Stack Underflow.  Quitting."<<endl;
        exit(-1);
    }
    else 
    {
       n = stack_num[stackpointer]; 
       stackpointer--;
       return n;
    }
}