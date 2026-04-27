CC = gcc 
CFLAGS = -Iinclude
OUT = main.exe

SRC = src/main.c \
	src/image.c \
	src/operacoes_aritmeticas.c \
	src/algoritmos_melhoramento.c\
	src/io.c \
	src/histograma.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	del $(OUT)

