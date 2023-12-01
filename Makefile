
input:
	gcc DataInput.c -g -o input

all:
	gcc Semaphore.c -g -o sem
	gcc Weatherforecast.c -g -o pred
	gcc sender.c -g -o send
	gcc receiver.c -g -o recv
	./sem
	./pred
	
client:
	./send

server:
	./recv

clean:
	rm input sem pred recv send *.txt
	
