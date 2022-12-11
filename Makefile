#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------


#Etapas para adicionar modulos:
#	1. Adicionar formula do objeto para saber o que eh necessario para sua compilacao
#	2. Adicionar objeto a variavel OBJS
#	3. Adicionar headers necessarios para compilacao em HDRS

CPP = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
#ADICIONAR NOS OBJETOS O QUE DEVE SER RASTREADO DE MUDANCA:
OBJS = $(OBJ)/main.o
#ADICIONAR NOS HEADERS OS INCLUDES NECESSARIOS PARA COMPILACAO:
HDRS = $(INC)/msgassert.h
CPFLAGS = -Wall -c -I$(INC)
CXXFLAGS = -std=c++11 -g -Wall

EXE = $(BIN)/quicksort

all:  $(EXE)

test: $(TEST)



$(BIN)/dictionary: $(OBJS)
	$(CPP) $(CXXFLAGS) -pg -I$(INC) -o $(BIN)/quicksort $(OBJS) $(LIBS) 

# Formulas para os objetos:

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CPP) $(CPFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/recQuicksort.o: $(HDRS) $(SRC)/recQuicksort.cpp
	$(CPP) $(CPFLAGS) -o $(OBJ)/recQuicksort.o $(SRC)/recQuicksort.cpp



	
	
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out