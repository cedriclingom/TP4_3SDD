#compilateur
CC = gcc



#Les options
CFLAGS = -ansi -pedantic -Wall -Wextra -g -O2
LDFALGS = -lm 



#Executable
EXEC = main


#Liste des fichiers objets
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)



#Règle d'exécution
all: $(EXEC)



#Règle de production de l'exécutable
main: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)





#Règle de production des fichiers objets
%.o: %.c
	$(CC) -c $< $(CFLAGS)



#Règle de nettoyage

.PHONY: clean mrpropre


clean:
	rm $(OBJ)

mrpropre: clean
	rm $(EXEC)

