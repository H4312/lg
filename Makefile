# Makefile TP LG

CC = g++
FLAGS = -g -c -o
SRC = src/
OBJ = obj/
INCLUDE = include/
EXEC_NAME = lg_H4312

$(EXEC_NAME) : $(OBJ)Automate.o $(OBJ)Etat.o $(OBJ)Lexer.o $(OBJ)Symbole.o $(OBJ)main.o
	$(CC) -g -o $(EXEC_NAME) -I $(INCLUDE) $^


$(OBJ)Automate.o: $(SRC)Automate.cpp $(INCLUDE)Automate.h
	$(CC) $(FLAGS) $@ -I $(INCLUDE) $(SRC)Automate.cpp

$(OBJ)Etat.o: $(SRC)Etat.cpp $(INCLUDE)Etat.h
	$(CC) $(FLAGS) $@ -I $(INCLUDE) $(SRC)Etat.cpp

$(OBJ)Lexer.o: $(SRC)Lexer.cpp $(INCLUDE)Lexer.h
	$(CC) $(FLAGS) $@ -I $(INCLUDE) $(SRC)Lexer.cpp

$(OBJ)Symbole.o: $(SRC)Symbole.cpp $(INCLUDE)Symbole.h
	$(CC) $(FLAGS) $@ -I $(INCLUDE) $(SRC)Symbole.cpp

$(OBJ)main.o: $(SRC)main.cpp $(INCLUDE)Automate.h $(INCLUDE)Etat.h $(INCLUDE)Lexer.h $(INCLUDE)Symbole.h 
	$(CC) -g -c -o $@ -I $(INCLUDE) $(SRC)main.cpp

clean :
	rm -f $(OBJ)*.o $(EXEC_NAME)

