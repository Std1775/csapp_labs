CC = gcc
CFLAGS = -O0 -g -Wall -Werror


all: qtest
	-tar -cf handin.tar queue.c queue.h Makefile

queue.o: queue.c queue.h harness.h
	$(CC) $(CFLAGS) -c queue.c

#you need to add queue.o to the build process and the linking process here
qtest: queue.o qtest.c report.c console.c harness.c 
	$(CC) $(CFLAGS) queue.o -o qtest qtest.c report.c console.c harness.c 

test: qtest driver.py
	chmod +x driver.py
	./driver.py

clean:
	rm -f *.o *~ qtest 
	rm -rf *.dSYM
	(cd traces; rm -f *~)

