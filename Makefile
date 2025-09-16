# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/12 13:28:44 by rel-qoqu          #+#    #+#              #
#    Updated: 2025/09/23 15:10:30 by smamalig         ###   ########.fr        #
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

GTEST_CFLAGS		:= $(shell pkg-config --cflags gtest gmock 2>/dev/null)
GTEST_LIBS			:= $(shell pkg-config --libs gtest gmock 2>/dev/null)
GTEST_MAIN_LIBS		:= $(shell pkg-config --libs gtest_main gmock_main 2>/dev/null)
ifneq ($(strip $(GTEST_MAIN_LIBS)),)
GTEST_LIBS          += $(GTEST_MAIN_LIBS)
endif
ifeq ($(strip $(GTEST_LIBS)),)
	GTEST_LIBS = -lgtest -lgtest_main -lgmock -lgmock_main -pthread
endif

CXX_FLAGS			+= $(INC_FLAGS) $(GTEST_CFLAGS)

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

ALLOCATOR_FILES	:= $(addprefix allocator/, init.c destroy.c alloc.c free.c \
					arena/alloc.c arena/free.c arena/new.c arena/create.c \
					arena/destroy.c arena/find.c \
					slab/alloc.c slab/free.c slab/create.c slab/destroy.c)
ARGS_FILES		:= $(addprefix arguments/, add.c destroy.c find.c get.c init.c \
					internal/arguments_parse.c internal/parse_long.c internal/positional.c \
					internal/parse_short.c)
BYTECODE_FILES	:= bytecode/write.c
DS_FILES		= ds/hash_table/hash_table_init.c ds/hash_table/hash_table_delete.c \
					ds/hash_table/hash_table_destroy.c ds/hash_table/hash_table_insert.c \
					ds/hash_table/hash_table_reset.c ds/hash_table/hash_table_search.c \
					ds/hash_table/internal/hash_table_resize.c \
					ds/string_table/string_table_add.c ds/string_table/string_table_core.c
SRC_FILES		:= main.c $(ALLOCATOR_FILES) $(ARGS_FILES) $(BYTECODE_FILES) $(DS_FILES)

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS			:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS			:= $(patsubst $(SRC_DIR)/%.c, $(DEP_DIR)/%.d, $(SRCS))

MAIN_FILE		= main.c
MAIN_SRC		= $(addprefix $(SRC_DIR)/,$(MAIN_FILE))
MAIN_OBJ		= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRC))
OBJS_NO_MAIN	= $(filter-out $(MAIN_OBJ), $(OBJS))

TEST_FILES		= hash_table_tests.cpp
TEST_SRCS		:= $(addprefix $(TEST_DIR)/, $(TEST_FILES))
TEST_OBJS		:= $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))
TEST_BIN		:= unit_tests

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(C_FLAGS) $(OBJS) $(RL_LIBS) $(LIBFT_A) -o $(NAME)

$(TEST_BIN): $(LIBFT_A) $(OBJS_NO_MAIN) $(TEST_OBJS)
	$(CXX) $(CXX_FLAGS) $(TEST_OBJS) $(OBJS_NO_MAIN) $(RL_LIBS) $(LIBFT_A) $(GTEST_LIBS) -o $(TEST_BIN)

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
	$(CXX) $(CXX_FLAGS) -c $< -o $@

clean:
	@rm -rf $(DEP_DIR)
	@rm -rf $(OBJ_DIR)*
	@rm -f $(TEST_BIN)
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

tests: $(TEST_BIN)
	@echo "Tests build OK: ./$(TEST_BIN)"

test: $(TEST_BIN)
	@if [ -n "$(FILTER)" ]; then \
		echo "Running tests matching: $(FILTER)"; \
		./$(TEST_BIN) --gtest_filter="$(FILTER)"; \
	else \
		echo "Running all tests"; \
		./$(TEST_BIN); \
	fi

.PHONY: all clean fclean re debug sanitize norm tests test

-include $(DEPS)

.SECONDARY: $(OBJS)
