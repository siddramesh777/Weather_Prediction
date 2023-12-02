
input:
	gcc DataInput.c -g -o input

all:
	gcc Semaphore.c -g -o sem
	gcc Weatherforecast.c -g -o pred
	gcc server.c -g -o ser
	gcc client.c -g -o cli
	./sem
	./pred
	
client:
	./cli

server:
	./ser

clean:
	rm input sem pred cli ser *.txt
	
