EXEC=bomberman
SOURCES=load.c main.c menu.c game.c
OBJECTS=$(SOURCES:.c=.o)
CC=gcc
CFLAGS=-std=gnu99 -Wall -Werror -lm
  
.PHONY: default clean
 
default: $(EXEC)
 
load.o: load.c load.h
game.o: game.c game.h load.h
menu.o: menu.c menu.h
main.o: main.c menu.h game.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
 
$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^
 
clean:
	rm -rf $(EXEC) $(OBJECTS) $(SOURCES:.c=.c~) $(SOURCES:.c=.h~) Makefile~
