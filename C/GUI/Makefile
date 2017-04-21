CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags gtk+-3.0`
LDFLAGS = -g 
OBJECTS = gtkMain.o panes.o display.o Treeview.o listview.o textview.o pathCreate.o
EXES = gtkMain 
LIBS = `pkg-config --libs gtk+-3.0`
$(EXES):	$(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS) $(LIBS)
	
all: $(EXES)
	
%.o:	%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXES)
