
# compiler settings/warning flags
CC = gcc
CFLAGS = -Wall -O3 -std=c99

# link to libraries (math.h)
LIBS = -lm

# names of executables etc..
EXECUTABLE = runme
TESTEXEC = test
TESTSRC = test.c
OUTPUT = result.txt

# get list of .c files in cwd - excluding test.c - testing is a separate program
SOURCES = $(filter-out $(TESTSRC), $(wildcard *.c))
#derive .o file list from SOURCES
OBJECTS = $(SOURCES:.c=.o)

# default rule
all: $(EXECUTABLE)

# produce executable from .o files
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $^ $(LIBS)

# compile c files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# test rule - compiles program then tests then makes clean
test: all
	$(CC) $(CFLAGS) -o $(TESTEXEC) $(TESTSRC)
	./$(TESTEXEC)
	make clean

# remove executables + obj files
clean: 
	rm -rf $(EXECUTABLE) $(TESTEXEC) $(OBJECTS) $(OUTPUT)