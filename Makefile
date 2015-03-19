#@IgnoreInspection BashAddShebang
# Makefile TP LG
FILES = Automate.cpp Etat.cpp Lexer.cpp Symbole.cpp

CC = g++
FLAGS = -g -c
BIN_DIR = bin/
SRCDIR = src/
OBJ_DIR = obj/
INCLUDE = include
EXEC_NAME = lg_H4312

OBJS = $(patsubst %.cpp,$(OBJ_DIR)%.o, $(FILES))
OBJS += $(OBJ_DIR)main.o
SRC :=  $(patsubst %.cpp,$(SRCDIR)%.cpp, $(FILES))
HEADER = $(patsubst %.cpp,$(INCLUDE)%.h, $(FILES))

all: $(BIN_DIR)$(EXEC_NAME)

$(BIN_DIR)$(EXEC_NAME): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) -g -o $@ $^

$(OBJ_DIR)%.o: $(SRCDIR)%.cpp
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I$(INCLUDE) -o $@  $^

$(OBJ_DIR)main.o : $(SRCDIR)main.cpp
	$(CC) $(FLAGS) -o $@ -I$(INCLUDE) $^


clean :
	rm -rf $(OBJ_DIR)

mr_proper : clean
	rm -rf bin/

