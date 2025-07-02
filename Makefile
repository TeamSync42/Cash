# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 11:03:00 by smamalig          #+#    #+#              #
#    Updated: 2025/07/02 12:16:22 by smamalig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cash
CC			= cc
CFLAGS		= -Wall -Wextra -MMD -MP
SRC_DIR		= src
OBJ_DIR		= obj

SRC_ARGS	:= arguments/init.c
SRC_FILES	:= $(SRC_ARGS) main.c

SRCS		:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS))

INCLUDES	= -Iinclude -Ilibft/include

RED			= \e[31m
GREEN		= \e[32m
YELLOW		= \e[33m
BLUE		= \e[34m
MAGENTA		= \e[35m
CYAN		= \e[36m
RESET		= \e[m

LIBFT		= libft
LIBFT_FLAGS	= -Llibft -lft
LIBFT_DIR	= ./libft

LDFLAGS		= $(LIBFT_FLAGS)

ifeq ($(DEBUG), 1)
	CFLAGS += -Wpedantic -Wpacked -O0 -g3
else
	CFLAGS += -Werror -ffast-math -O3
endif

all: $(NAME)

bonus: $(NAME)

-include $(DEPS)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean:
	@printf "$(BLUE)%s$(RESET): $(RED)Removing$(RESET) object files\n" $(NAME)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@printf "$(BLUE)%s$(RESET): $(RED)Removing$(RESET) executables and libraries\n" $(NAME)
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean
	@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re bonus $(LIBFT)

