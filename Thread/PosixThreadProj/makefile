workcrew : control.o queue.o workcrew.o
	cc -o workcrew control.o queue.o workcrew.o -pthread

control.o : control.c control.h
	cc -c control.c
queue.o : queue.c queue.h
	cc -c queue.c
workcrew.o : workcrew.c debug.h queue.h control.h
	cc -c workcrew.c

clean:
	rm workcrew workcrew.o queue.o control.o

