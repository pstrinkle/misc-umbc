Author:  Patrick Trinkle
Email:   tri1@umbc.edu
Course:  CMSC481
Project: Project 2

This program implements a very specific memory management system using logical address paging and special input executable ascii documents.  The program should execute commands properly and typos are taken as improper commands, either in the command interpreter or in the executing mechanism for the ascii executables.  If an executable cannot fit into main memory when loaded it is placed in virtual memory only if it could theoretically fit into main memory at some point to execute.  These executables are loaded in as processes and assigned process ids.

A note for executing this program is that if you fill virtual memory and main memory to the point where there is no feasible swapping to properly allocate free space to execute a process an endless loop will initiate trying to swap processes out of main memory into virtual memory, which is already too full to accept.  This is a weakness in the program that could not be designed around.  When the program needs to move the least recently used process into virtual memory, if the least recently used process is already in virtual memory it moves that process to the front of the queue, and then tries the "new" least recently used process, it does the same thing if the least recently used process won't fit into virtual memory.

Also note that when a process is copied from main to virtual or vice-versa the values in the memory are copied back and forth.  This is a O(n) process where n is the number of bytes allocated for the process.  The sorting algorithm used to sort the pids for listpr is O(n^2) which isn't a huge deal if n is small which is typically has been.