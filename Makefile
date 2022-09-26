TARGET = sujkovic_p1
CC = g++
FLAGS = -Wall -Wextra -g

all: $(TARGET)

$(TARGET): sujkovic_p1.o
	$(CC) sujkovic_p1.o -o $@

sujkovic_p1.o: sujkovic_p1.cpp Parser.h
	$(CC) $(FLAGS) -c sujkovic_p1.cpp -o $@

clean:
	rm -rf *.o $(TARGET)