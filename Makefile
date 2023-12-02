
input:
	gcc DataInput.c -g -o input

all:
	gcc Semaphore.c -g -o cli
	gcc server.c -g -o ser
	./sem
	./pred
	
client:
	./cli

server:
	./ser

clean:
	rm input sem pred recv send *.txt
	
