# Declaration of variables
CC = gcc
CC_FLAGS = -Wall

# File names
EXEC = run
CLEAR = clear
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	$(CLEAR)
	rm -f $(EXEC) $(OBJECTS)
