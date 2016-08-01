# Paulo Garcia and Roel Ronquillo
# Assignment 3 Indexer

CC=gcc
FLAGS= -Wall -g

all: index

index: indexlib.a
	$(CC) $(FLAGS) -o indexer index.c indexlib.a
	

indexlib.a: tokenizer.o SortedList.o fileReader.o indexer.o
	ar -cvq indexlib.a  tokenizer.o SortedList.o fileReader.o indexer.o 

indexer.o:
	$(CC) $(Flags) -c indexer.c indexer.h
	
fileReader.o:
	$(CC) $(Flags) -c fileReader.c fileReader.h
	
SortedList.o:
	$(CC) $(Flags) -c SortedList.c SortedList.h

tokenizer.o:
	$(CC) $(Flags) -c tokenizer.c tokenizer.h
	
clean:
	rm *.o *.a *.gch indexer a.out