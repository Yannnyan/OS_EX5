# compiler
CC = g++
# paths
SOURCE_STACK_PATH = sources/Stack
SOURCE_HEAP_PATH = sources/Heap
SOURCE_SERVER_PATH = sources/Server
SOURCE_CLIENT_PATH = sources/Client
SOURCE_AUXILARY_PATH = sources/Auxilary
SOURCE_PROCESS_PATH = sources/Process
OBJECT_PATH = objects/
# wildcards for .cpp files inside sources folder
# generate all the .cpp files for the stack folder inside sources
SOURCES_STACK = $(wildcard $(SOURCE_STACK_PATH)/*.cpp)
SOURCES_HEAP = $(wildcard $(SOURCE_HEAP_PATH)/*.cpp)
SOURCES_SERVER = $(wildcard $(SOURCE_SERVER_PATH)/*.cpp)
SOURCES_CLIENT = $(wildcard $(SOURCE_CLIENT_PATH)/*.cpp)
SOURCES_AUXILARY = $(wildcard $(SOURCE_AUXILARY_PATH)/*.cpp)
SOURCES_PROCESS = $(wildcard $(SOURCE_PROCESS_PATH)/*.cpp)
# wildcards for hpp files
# generate all the .hpp files for the stack folder inside sources
HEADERS_STACK = $(wildcard $(SOURCE_STACK_PATH)/*.hpp)
HEADERS_HEAP = $(wildcard $(SOURCE_HEAP_PATH)/*.hpp)
HEADERS_SERVER = $(wildcard $(SOURCE_SERVER_PATH)/*.hpp)
HEADERS_CLIENT = $(wildcard $(SOURCE_CLIENT_PATH)/*.hpp)
HEADERS_AUXILARY = $(wildcard $(SOURCE_AUXILARY_PATH)/*.hpp)
HEADERS_PROCESS = $(wildcard $(SOURCE_PROCESS_PATH)/*.hpp)
# set up Object files
# set up .o files to link by swapping each .cpp to .o
# then swapping the folder location to objects for the destination of the object file
# take the file name from the stack .cpp files and change their ending to .o and then change the folder to be objects folder
OBJECTS_STACK = $(subst sources/Stack,$(OBJECT_PATH),$(subst .cpp,.o,$(SOURCES_STACK)))
OBJECTS_HEAP = $(subst sources/Heap,$(OBJECT_PATH),$(subst .cpp,.o,$(SOURCES_HEAP)))
OBJECTS_SERVER = $(subst sources/Server,$(OBJECT_PATH),$(subst .cpp,.o,$(SOURCES_SERVER)))
OBJECTS_CLIENT = $(subst sources/Client,$(OBJECT_PATH),$(subst .cpp,.o,$(SOURCES_CLIENT)))
OBJECTS_AUXILARY = $(subst sources/Auxilary,$(OBJECT_PATH),$(subst .cpp,.o,$(SOURCES_AUXILARY)))
OBJECTS_PROCESS = $(subst sources/Process,$(OBJECT_PATH),$(subst .cpp,.o,$(SOURCES_PROCESS)))
# flags
CFLAGS = -Wall -g -pthread $(SOURCE_PATH)
# headers
DEPS = $(HEADERS_SERVER) $(HEADERS_AUXILARY) $(HEADERS_HEAP) $(HEADERS_CLIENT) $(HEADERS_PROCESS)

all: Server Client 

Server: $(OBJECTS_SERVER) $(OBJECTS_STACK) $(OBJECTS_HEAP) $(OBJECTS_AUXILARY) $(OBJECTS_PROCESS)
	$(CC) $(CFLAGS) $^ -o $@

Client: $(OBJECTS_CLIENT)
	$(CC) $(CFLAGS) $^ -o $@

testServer : TestServer.o TestRunner.o $(OBJECTS_HEAP)
	$(CC) $(CFLAGS) $^ -o $@ 

testClient : TestRunner.o TestClient.o 
	$(CC) $(CFLAGS) $^ -o $@ 

testHeap : TestRunner.o TestHeap.o $(OBJECTS_HEAP)
	$(CC) $(CFLAGS) $^ -o $@ 

testStack : TestRunner.o TestStack.o $(OBJECTS_STACK) $(OBJECTS_HEAP)
	$(CC) $(CFLAGS) $^ -o $@

main : main.o $(OBJECTS_STACK) $(OBJECTS_HEAP) $(OBJECTS_AUXILARY) $(OBJECTS_PROCESS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJECTS_STACK): $(SOURCES_STACK) $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS_HEAP): $(SOURCES_HEAP) $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJECTS_SERVER): $(SOURCES_SERVER) $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS_AUXILARY): $(SOURCES_AUXILARY) $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS_CLIENT): $(SOURCES_CLIENT) $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS_PROCESS): $(SOURCES_PROCESS) $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean: 
	rm -f $(OBJECTS_CLIENT) $(OBJECTS_HEAP) $(OBJECTS_SERVER) $(OBJECTS_STACK) $(OBJECTS_AUXILARY) $(OBJECTS_PROCESS)
	rm -f Server Client testStack testHeap testServer testClient main
	rm -f *.o 
	rm -f file.txt
