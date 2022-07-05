CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all:  $(SOURCES) $(EXECUTABLE) post_build

$(EXECUTABLE): $(SOURCES) 
	$(CC) $(LDFLAGS) $(SOURCES) -o $@

# main: main.c
# 	$(CC) main.c -o main

post_build: post_build.py
	@python3 post_build.py