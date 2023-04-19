# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
 
# executables
gatorTaxi: gatorTaxi.cpp RBT.h min_heap.h node.h
	$(CC) node.h
	$(CC) min_heap.h
	$(CC) RBT.h
	$(CC) gatorTaxi.cpp -o gatorTaxi

TARGET: output_file.txt

output_file.txt: input.txt
	./gatorTaxi < input.txt > output_file.txt

clean:
	$(RM) $(TARGET)