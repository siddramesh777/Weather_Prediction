
input:
	gcc DataInput.c -g -o input

all:
	gcc Weatherforecast.c -g -o pred
	gcc Semaphore.c -g -o sem
	gcc server.c -g -o ser
	gcc client.c -g -o cli
	./sem
	./pred
	
client:
	./cli

server:
	./ser

clean:
	rm input sem pred recv send *.txt
	
