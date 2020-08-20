#!/usr/bin/python


#MOUSE Programming Language Interpreter
#by Dave Vest
#as described by Peter Grogono in
#MOUSE: A programming language for microcomputers
#(c)1983
#
#Credit for the stack functions go to TryToProgram web site
#http://www.trytoprogram.com/c-programming/stack-in-c/

import sys

maxproglen = 1000
charpos = 0
stack = []
prog = []
 
if len(sys.argv) != 2:
    print("No MOUSE program file named on command line.\nUsage: mouse.py hello.mouse")
    sys.exit()

is_it_mouse = sys.argv[1].split('.')
if is_it_mouse[1] != "mouse":
    print "The file on the command line did not end with .mouse, sorry."
    sys.exit()



try:
    file_handle = open(sys.argv[1], "r")
except:
    print "File doesn't exist, sorry."
    file_handle.close()
    sys.exit()
else:
    #determine end of file
    x = file_handle.readlines()
    file_length = file_handle.tell()
    #reset to beginning of file
    file_handle.seek(0)

    #read file, character by character
    while file_handle.tell() != file_length:
        ch = file_handle.read(1)
        # ~ begins a comment.  Remove from ~ to next newline
        if ch == '~':
            while ch != '\n':
                ch = file_handle.read(1)
                charpos -= 1
        
        charpos += 1
        prog.append(ch)

#close file handle and file
file_handle.close()

if len(prog) > maxproglen:
    print "Your mouse program is too long."
    sys.exit()

charpos = 0
ch = ''

while ch != '$':
    ch = prog[charpos]
    if ch.isdigit():
        temp = 0
        while ch.isdigit():
            temp = 10 * temp + int(ch)
            charpos += 1
            ch = prog[charpos]

        stack.append(temp) 
        charpos -= 1

    charpos += 1

print stack.pop()
print "Program End"







