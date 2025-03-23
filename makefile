# Set g++ as the C++ compiler
CC=g++

# Enforce C++ 2011 as the language standard
CFLAGS=-std=c++11 

# Enable all standard warnings
# Enable uninitialized variable warnings,  and treat all warnings as errors
CFLAGS+= -Wall -Wuninitialized -Werror

# NOTE: Uncomment the following line to check if there are any memory leaks or not
# CFLAGS+=-fsanitize=address -fsanitize=undefined

# Object Files
OBJS=linkedlist.o polycalculator.o main.o

# Target
TARGET=polycalculator

$(TARGET): $(OBJS)
	@echo "Linking: $(OBJS) -> $@"
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
linkedlist.o:	linkedlist.h linkedlist.cpp
	@echo "Compiling: $^ -> $@"
	$(CC) $(CFLAGS) -c linkedlist.cpp
polycalculator.o: polycalculator.h polycalculator.cpp
	@echo "Compiling: $^ -> $@"
	$(CC) $(CFLAGS) -c  polycalculator.cpp
main.o:	main.cpp
	@echo "Compiling: $< -> $@"
	$(CC) $(CFLAGS) -c  main.cpp
clean:
	@echo "Deleting: $(OBJS) $(TARGET)"
	rm -rf $(OBJS) $(TARGET)
