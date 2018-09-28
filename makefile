#Makefile previsto per il progetto AES
#written by Riccardo Fontanini
OBJECTS=

#compiler
CC=gcc

#general flags
CFLAGS= 

#libs

ARGS=fontanini,$(D)

NAMEFILE = main.c
PROGRAM_NAME = communicator

cap_lib:
	$(CC) $(CFLAGS) -c libs/cap.c -o build/cap_lib.o -std=gnu99


$(PROGRAM_NAME): cap_lib
	@mkdir -p build
	$(CC) $(CFLAGS) $(NAMEFILE) -o build/$(PROGRAM_NAME) build/cap_lib.o -std=gnu99
	@echo " "
	@echo "Compilazione completata! il file si trova nella cartella build!"
	@echo " "

