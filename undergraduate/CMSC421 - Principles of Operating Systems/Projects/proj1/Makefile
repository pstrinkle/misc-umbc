
make:
	gcc -Wall -ansi -lm -lpthread -o pf pf.c
	gcc -Wall -ansi -o dm dm.c

pf:
	gcc -Wall -ansi -lm -lpthread -o pf pf.c

dm:
	gcc -Wall -ansi -o dm dm.c

test:
	./dm -m 5 -s 100 -d 10 -z 10 -c 10 -b 12 -u 7 -e 15 -h 10 -r 15 -n 105094

cleanest:
	rm -rf *~ core.* *# *.o pf dm out*.txt
