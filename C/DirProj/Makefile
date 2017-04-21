CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -g
OBJECTS = tokenizer.o commandLine.o execute.o changeDirectory.o redirect.o addtoPath.o
EXES = commandLine 

$(EXES):	$(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS)
	
all: $(EXES)
	
%.o:	%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXES)
