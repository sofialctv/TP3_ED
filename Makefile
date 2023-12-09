# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -Wall -Wextra

# Source files
SRCS = main.c simulation.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = hospital

# Phony targets
.PHONY: all compile run clean

# Default target (compile and run)
all: compile run

# Explicit compile target (produces the target program)
compile: $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)