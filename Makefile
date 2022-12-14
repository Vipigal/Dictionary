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
OBJS = $(OBJ)/main.o $(OBJ)/AVLDic.o $(OBJ)/HashDic.o $(OBJ)/recQuicksort.o 
#ADICIONAR NOS HEADERS OS INCLUDES NECESSARIOS PARA COMPILACAO:
HDRS = $(INC)/msgAssert.h $(INC)/HashDic.hpp $(INC)/AVLDic.hpp $(INC)/Dicionario.hpp $(INC)/recQuicksort.hpp $(INC)/lista.hpp 
CPFLAGS = -Wall -c -I$(INC)
CXXFLAGS = -std=c++11 -g -Wall

EXE = $(BIN)/dictionary

all:  $(EXE)

test: $(TEST)



$(BIN)/dictionary: $(OBJS)
	$(CPP) $(CXXFLAGS) -I$(INC) -o $(BIN)/dictionary $(OBJS) $(LIBS) 

# Formulas para os objetos:

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CPP) $(CPFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp -g

$(OBJ)/AVLDic.o: $(HDRS) $(SRC)/AVLDic.cpp
	$(CPP) $(CPFLAGS) -o $(OBJ)/AVLDic.o $(SRC)/AVLDic.cpp

$(OBJ)/HashDic.o: $(HDRS) $(SRC)/HashDic.cpp
	$(CPP) $(CPFLAGS) -o $(OBJ)/HashDic.o $(SRC)/HashDic.cpp -g


$(OBJ)/recQuicksort.o: $(HDRS) $(SRC)/recQuicksort.cpp
	$(CPP) $(CPFLAGS) -o $(OBJ)/recQuicksort.o $(SRC)/recQuicksort.cpp


	
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out