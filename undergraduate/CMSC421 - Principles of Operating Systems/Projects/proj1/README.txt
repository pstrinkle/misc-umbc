Readme for CMSC421 Project 1.

Author: Patrick Trinkle
email: tri1@umbc.edu
date: March 1, 2006

Files included: Makefile pf.c pf.h dm.c dm.h typescript COMMENTS.txt README.txt

To make both programs, run: make
Ignore warnings, that's just a strange library thing, the program compiles fine.

pf.c is a program which given a set of parameters will calculate the prime factorial of a given number N.  This program utilizes Pthreads.

To make this program specifically: make pf
To run: ./pf -n N -p P -q 
Where N is the number you wish to prime factorialize, P is the number of threads you wish to use to calculate the primes from 1 to N, and Q is the number of threads you wish to use to calculate of those primes, which are factors of N.  Of note, some systems can only handle so many threads from a program, so there is a limit.  Also of note, if you set P much greater than N the system will terminate.  If you use more Q threads than neccessary a similar behavior may occur.  So when deciding how many threads to use, be conserative.  If you need any command line information,
run: ./pf -h
To get a basic help screen.

dm.c is a program which given a very long set of parameters will model the producer consumer problem utilizing processes, semaphores, and shared memory, in the context of a Doonut Shop and Students.  

To make this program specifically run: make dm
To run this program: ./dm -m M -s S -d D -z Z -c C -b B -u U -e E -h H -r R -n N

Where the following are what those mean:
     
     M is the maximum number of doonut makers, M >= 5.  The number used is chosen at random between 5 and the maximum.
     S is the number of shelves on which the doonuts are placed, and from which the doonuts are eaten
     D is the maximum number of doonuts per shelf
     Z is the milliseconds the maker naps after matching a batch
     C is the milliseconds it takes to make a doonut
     B is the number of doonuts per batch
     U is the maximum number of students, U >= 7.  The number used is chosen at random between 7 and the maximum.
     E is the milliseconds required to eat a doonut.
     H is the number of doonuts a student will consume before the student is no longer hungry and goes to study.
     R is the milliseconds the student studies after consuming the H doonuts.
     N is the number used to seed the random number generator.

Note:
	Doonuts makers have an equal probability chance to either nap first, or make doonuts first.
	Students will always start hungry.

	Many output files are created when running this program, so write permissions are required for the folder in which this runs.  They are named, out_baker_#.txt, out_student_#.txt, # defined as the id of that process.  The program runs without output to STDOUT, but will properly end all child processes and destroy all semaphores and shared memory created.

	If you terminate the program while running, to find and delete semaphores and shared memory segments created, run: ipcs to view them, and then ipcrm -m sharedmemoryid, ipcrm -s semaphoreid, see: man ipcs, man ipcrm for more information.

	Max Pthreads 254 for pf program.