# Nome do executável
EXEC = juros

# Diretórios
SRC_DIR = .
BIN_DIR = ../bin

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# IMPORTANTE: biblioteca matemática
LDFLAGS = -lm

# Arquivos fonte
SRCS = juros.c calculos.c prints.c vetor.c

# Objetos no bin
OBJS = $(SRCS:%.c=$(BIN_DIR)/%.o)

# Regra principal
tudo: $(BIN_DIR)/$(EXEC)

# Linkagem final (AGORA COM -lm)
$(BIN_DIR)/$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilação
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza de .o
limpa:
	rm -f $(BIN_DIR)/*.o

# Limpeza total
faxina: limpa
	rm -f $(BIN_DIR)/$(EXEC)