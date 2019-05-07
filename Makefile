#Makefile

PROJ_NAME = tradutor

CC = g++

CC_FLAGS = -c \
           --std=c++11

OBJ = main.o pre_processor.o parser.o scanner.o


 
all: $(PROJ_NAME)
	rm -rf $(OBJ)

 
$(PROJ_NAME): $(OBJ)	
	$(CC) -o $(PROJ_NAME) $(OBJ)

scanner.o: scanner.cpp scanner.hpp
	$(CC) $(CC_FLAGS) scanner.cpp

parser.o: parser.cpp parser.hpp scanner.o
	$(CC) $(CC_FLAGS) parser.cpp scanner.cpp

pre_processor.o: pre_processor.cpp pre_processor.hpp parser.o scanner.o
	$(CC) $(CC_FLAGS) pre_processor.cpp parser.cpp scanner.cpp

main.o: main.cpp pre_processor.o parser.o scanner.o
	$(CC) $(CC_FLAGS) main.cpp pre_processor.cpp parser.cpp scanner.cpp


	