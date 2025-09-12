# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/12 13:28:44 by rel-qoqu          #+#    #+#              #
#    Updated: 2025/09/12 17:39:06 by rel-qoqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell

SRC_DIR				= ./src
INC_DIR				= ./include
TEST_DIR			= ./test
OBJ_DIR				= ./obj
DEP_DIR				= ./.deps
LIBS_DIR			= ./lib

INC_FLAGS			= -I$(INC_DIR) -I$(LIBS_DIR)/libft/include

CC					= cc
CXX					= c++
C_FLAGS				= -std=c17 -Wall -Wextra -Werror -pedantic -MMD -MP $(INC_FLAGS)
C_DEBUG_FLAGS		= -Og -g3 -DDEBUG -Wshadow -Wconversion -Wstrict-prototypes \
						-Wmissing-prototypes -Wmissing-declarations -Winline -Wsign-conversion \
						-Wundef -Wcast-align -Wcast-qual -Wwrite-strings -Wuninitialized \
						-Wdouble-promotion -Wvla -Wnull-dereference -Wold-style-definition -Wpadded
C_RELEASE_FLAGS		= -O3 -march=native -funroll-loops -fomit-frame-pointer -DNDEBUG
CXX_FLAGS			= -std=c++17 -Wall -Wextra -Werror -pedantic
CXX_RELEASE_FLAGS	= -O3 -flto -march=native -funroll-loops -fomit-frame-pointer -DNDEBUG
CXX_DEBUG_FLAGS		= -Og -g3 -DDEBUG

LIBFT_A				= $(LIBS_DIR)/libft/libft.a

RL_CFLAGS			:= $(shell pkg-config --cflags readline 2>/dev/null)
RL_LIBS				:= $(shell pkg-config --libs readline 2>/dev/null)
ifeq ($(RL_LIBS),)
	RL_LIBS	= -lreadline
endif

MODE				:= release
ifeq ($(MODE), release)
	C_FLAGS += $(C_RELEASE_FLAGS)
	CXX_FLAGS += $(CXX_RELEASE_FLAGS)
else ifeq ($(MODE), debug)
	C_FLAGS += $(C_DEBUG_FLAGS)
	CXX_FLAGS += $(CXX_DEBUG_FLAGS)
	NAME = minishell_debug
	OBJ_DIR = obj_debug
else ifeq ($(MODE), sanitize)
	C_FLAGS += $(C_DEBUG_FLAGS) -fsanitize=address
	CXX_FLAGS += $(CXX_DEBUG_FLAGS) -fsanitize=address
	NAME = minishell_sanitize
	OBJ_DIR = obj_sanitize
endif

DS_FILES		= ds/hash_table_create.c ds/hash_table_delete.c ds/hash_table_destroy.c \
					ds/hash_table_insert.c ds/hash_table_reset.c ds/hash_table_search.c
SRC_FILES		= main.c $(DS_FILES)

SRCS			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS			= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS			= $(patsubst $(SRC_DIR)/%.c, $(DEP_DIR)/%.d, $(SRCS))

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) $(RL_LIBS) $(LIBFT_A) -o $(NAME)

ifeq ($(MODE), debug)
$(LIBFT_A):
	$(MAKE) -C $(LIBS_DIR)/libft debug
else ifeq ($(MODE), sanitize)
$(LIBFT_A):
	$(MAKE) -C $(LIBS_DIR)/libft sanitize
else ifeq ($(MODE), release)
$(LIBFT_A):
	$(MAKE) -C $(LIBS_DIR)/libft
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D) $(DEP_DIR)
	$(CC) $(C_FLAGS) -c $< -o $@ -MF $(DEP_DIR)/$(*F).d

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	@rm -rf $(DEP_DIR)
	@rm -rf $(OBJ_DIR)*
	$(MAKE) -C $(LIBS_DIR)/libft clean

fclean: clean
	@rm -f $(NAME)*
	$(MAKE) -C $(LIBS_DIR)/libft fclean

re: fclean all

debug:
	$(MAKE) MODE=debug

sanitize:
	$(MAKE) MODE=sanitize

norm:
	@norminette $(INC_DIR)
	@norminette $(SRC_DIR)

tests:
	@echo "OK"

test:
	@if [ -n "$(FILTER)" ]; then \
  		echo "Running tests matching: $(FILTER)"; \
  	else \
		echo "Please specify FILTER=pattern"; \
		echo "Example: make test FILTER='*lexer*'"; \
		exit 42; \
	fi

.PHONY: all clean fclean re debug sanitize norm tests test

-include $(DEPS)

.SECONDARY: $(OBJS)
