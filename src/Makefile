# Nome do executável
EXEC = juros

# Diretórios
SRC_DIR = .
# Agora o executável vai para a raiz (um nível acima de src)
ROOT_DIR = ..
# Os objetos continuam indo para uma pasta bin para não sujar a src
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
# Agora depende da raiz para o executável e do bin para os objetos
tudo: $(BIN_DIR) $(ROOT_DIR)/$(EXEC)

# Regra para criar o diretório bin (caso não exista)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Linkagem final: O destino agora é $(ROOT_DIR)/$(EXEC)
$(ROOT_DIR)/$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilação
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza de .o
limpa:
	rm -f $(BIN_DIR)/*.o

# Limpeza total: remove objetos e o executável da raiz
faxina: limpa
	rm -f $(ROOT_DIR)/$(EXEC)