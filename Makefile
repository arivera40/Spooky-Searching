all:
	@echo "Error: must choose 'proc' or 'thread' only;"

proc: multitest_proc.o searchtest.c
	gcc -D proc -o searchtest multitest_proc.o searchtest.c

thread: multitest_thread.o searchtest.o 
	gcc -D thread -pthread -o searchtest multitest_thread.o searchtest.o

searchtest.o: searchtest.c multitest.h
	gcc -c searchtest.c multitest.h

multitest_proc.o: multitest_proc.c
	gcc -c multitest_proc.c

multitest_thread.o: multitest_thread.c
	gcc -c multitest_thread.c

clean:
	-rm -f *.o
	-rm -f searchtest
	-rm -f *h.gch
