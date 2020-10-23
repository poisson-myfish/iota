CC=gcc
CFLAGS=-c -Wall -Wextra -I include/
LFLAGS=-O2

EXEC=iota
SOURCES=$(wildcard src/*.c)
OBJECTS=$(patsubst src/%.c, objects/%.o, $(SOURCES))
HEADERS=$(wildcard include/*.h)

objects/%.o: src/%.c $(HEADERS)
	@mkdir -p objects
	@echo [COMPILE] $<
	@$(CC) $(CFLAGS) $< -o $@

$(EXEC): $(OBJECTS)
	@echo [LINK] $(EXEC)
	@$(CC) $(LFLAGS) $(OBJECTS) -o $(EXEC)

clean:
	@rm objects/*.o
	@rm iota

compile-examples:
	@./iota
	@llc -filetype=obj milestone.ll
	@gcc milestone.o -o milestone
