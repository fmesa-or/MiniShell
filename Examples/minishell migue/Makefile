# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 19:23:12 by migumar2          #+#    #+#              #
#    Updated: 2024/07/17 14:03:48 by jholland         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INCLUDES = -Iinclude -lreadline #-fsanitize=address -fno-omit-frame-pointer

#LIBFT

LIBFT_DIR = lib/libft
LIBFT_SRC = ft_calloc.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c \
			ft_substr.c ft_itoa.c ft_atoi.c ft_isalpha.c
LIBFT = $(addprefix $(LIBFT_DIR)/,$(LIBFT_SRC))

# UTILS

UTILS_DIR = src/utils
UTILS_SRC = same_string.c ft_isalnum.c ft_isspace.c ft_strncmp.c ft_strcmp.c free_ptr_array.c find_equal.c
UTILS = $(addprefix $(UTILS_DIR)/,$(UTILS_SRC))

# MINISHELL

INPUT_DIR = src/input
INPUT_SRC = user_input.c syntax.c
INPUT = $(addprefix $(INPUT_DIR)/,$(INPUT_SRC))

ENV_DIR = src/environment
ENV_SRC = create_var_list.c use_var_list.c
ENV = $(addprefix $(ENV_DIR)/,$(ENV_SRC))

PARSING_DIR = src/parsing
PARSING_SRC = allocation.c parse_arg.c
PARSING = $(addprefix $(PARSING_DIR)/,$(PARSING_SRC))

TOKENS_DIR = src/tokens
TOKENS_SRC = get_tokens.c tk_add_redir.c free_token_list.c tk_set_command.c get_arg.c
TOKENS = $(addprefix $(TOKENS_DIR)/,$(TOKENS_SRC))

BUILTIN_DIR = src/builtins
BUILTIN_SRC = builtins.c ft_cd.c ft_env.c ft_exit.c ft_export.c ft_pwd.c \
				ft_unset.c echo/ft_echo.c echo/hexa_char.c echo/octal_char.c \
				echo/echo_options.c echo/escapes.c
BUILTIN = $(addprefix $(BUILTIN_DIR)/,$(BUILTIN_SRC))

EXEC_DIR = src/execution
EXEC_SRC = pipe.c redir.c find_path.c prepare_to_execute.c execution.c heredoc.c
EXEC = $(addprefix $(EXEC_DIR)/,$(EXEC_SRC))

SRC = 	$(LIBFT) $(UTILS) $(INPUT) $(ENV) $(PARSING) $(TOKENS) $(BUILTIN) $(EXEC) \
		src/minishell.c src/prints.c src/signal.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -g -o $(NAME) $(OBJ) $(INCLUDES)

%.o: %.c
	@gcc -Wall -Werror -Wextra -g -c $< -o $@ $(INCLUDES)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re