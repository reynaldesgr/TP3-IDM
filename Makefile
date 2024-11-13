# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Source files (specifying the 'src' directory)
SRCS = main.c src/objet_graphique.c

# Object files (will be created in the same directory as the Makefile)
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = tp_poc

# Default target
all: $(TARGET)

# Linking the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compiling the source files to object files
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
