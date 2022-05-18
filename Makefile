CC = g++
CFLAGS = -Wall -g -pthread

all: Server Client

Server: Server.o
	$(CC) $^ -o $@ $(CFLAGS)

Client: Client.o
	$(CC) $^ -o $@ $(CFLAGS)

example: example.o
	$(CC) $^ -o $@

writeFile: writeFile.o
	$(CC) $^ -o $@

main: main.o heap_funcs.o
	$(CC) $^ -o $@

Test: Test_Stack_mmap.o Stack.o
	$(CC) $^ -o $@

%.o : %.cpp
	$(CC) -o $@ -c $^ $(CFLAGS)

PHONY: clean

clean:
	rm -f *.o Server Client example writeFile Test stack.txt file.txt main
