# Makefile para o TAD de AVL
# Estrutura de Dados II - EINF_T2 - G8

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99 -I include
LDFLAGS =

# Directórios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Nome do executável
TARGET = avl

# Ficheiros fonte
SRC_FILES = main.c avl.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Headers
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Cores para output
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

# Regra principal
all: $(OBJ_DIR) $(TARGET)
	@echo "$(GREEN)✓ Compilação concluída com sucesso!$(NC)"
	@echo "$(YELLOW)→ Execute com: ./$(TARGET)$(NC)"

# Criar directório de objectos
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Linkagem
$(TARGET): $(OBJS)
	@echo "$(YELLOW)Linkando objetos...$(NC)"
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilação de ficheiros .c para .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "$(YELLOW)Compilando $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos ficheiros objetos
clean:
	@echo "$(RED)Removendo ficheiros objeto...$(NC)"
	rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✓ Limpeza concluída!$(NC)"

# Limpeza completa (objetos + executável)
fclean: clean
	@echo "$(RED)Removendo executável...$(NC)"
	rm -f $(TARGET)
	@echo "$(GREEN)✓ Limpeza completa concluída!$(NC)"

# Recompilação completa
re: fclean all

# Executar o programa
run: $(TARGET)
	@echo "$(GREEN)Iniciando o programa...$(NC)"
	./$(TARGET)

# Verificar memória com Valgrind
valgrind: $(TARGET)
	@echo "$(YELLOW)Executando com Valgrind...$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Ajuda
help:
	@echo "╔════════════════════════════════════════════════════════════╗"
	@echo "║          MAKEFILE - Sistema de Voto Electrónico            ║"
	@echo "╠════════════════════════════════════════════════════════════╣"
	@echo "║  make        - Compila o programa                          ║"
	@echo "║  make clean  - Remove ficheiros .o                         ║"
	@echo "║  make fclean - Remove .o e executável                      ║"
	@echo "║  make re     - Recompila tudo                              ║"
	@echo "║  make run    - Compila e executa                           ║"
	@echo "║  make valgrind - Executa com verificação de memória        ║"
	@echo "║  make help   - Mostra esta ajuda                           ║"
	@echo "╚════════════════════════════════════════════════════════════╝"

# Marcar alvos que não são ficheiros
.PHONY: all clean fclean re run valgrind help