# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 15:59:19 by fmesa-or          #+#    #+#              #
#    Updated: 2025/05/30 14:15:09 by fmesa-or         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Name
NAME		:= minishell

#Compile
CC			:= cc

#Flags
CFLAGS		:= -Wall -Wextra -Werror -g

#Clean
CLEAN		:= rm -Rf

#Sources
SRCS_DIR	:= src
SRCS		:= src/minishell.c \
			src/execute/builtins/cd_pwd.c \
			src/execute/builtins/echo.c \
			src/execute/builtins/env.c \
			src/execute/builtins/ex_buil.c \
			src/execute/builtins/exit.c \
			src/execute/builtins/unset.c \
			src/execute/builtins/export/export.c \
			src/execute/builtins/export/var_list.c \
			src/execute/exe_redir/exe_redir.c \
			src/execute/exe_redir/exe_redir2.c \
			src/execute/exe_redir/ms_fds.c \
			src/execute/exe_redir/ms_hdoc.c \
			src/execute/exe_redir/sherpa.c \
			src/execute/exe_redir/tin_opener.c \
			src/execute/execution/childs.c \
			src/execute/execution/execute.c \
			src/execute/execution/ms_comdr.c \
			src/execute/execution/post_exe.c \
			src/execute/utils_exe/utils_exe.c \
			src/execute/utils_exe/utils_exe2.c \
			src/mem/mem_man.c \
			src/mem/mem_tabl.c \
			src/mem/mem_tabl2.c \
			src/mem/mem_utils.c \
			src/parse/is_buicmd.c \
			src/parse/par_utils.c \
			src/parse/parse.c \
			src/parse/pipe_sep.c \
			src/parse/redir.c \
			src/parse/tk_init.c \
			src/parse/token_list.c \
			src/parse/expand/exp_utils.c \
			src/parse/expand/expand.c \
			src/parse/get_argv/get_argv.c \
			src/parse/get_argv/ms_q_loop.c \
			src/prompt/prompt.c \
			src/prompt/prompt2.c \
			src/signals/signals.c \
			src/signals/signalshd.c \
			src/utils/envtolist.c \
			src/utils/errors.c \
			src/utils/freedom.c \
			src/utils/ft_itoa.c \
			src/utils/ft_scjoin.c \
			src/utils/l_convers.c \
			src/utils/list_utils.c \
			src/utils/red_utils.c \
			src/utils/str_utils.c \
			src/utils/split/split.c \
			src/utils/split/split2.c

#Objects
OBJS_DIR	:= obj
OBJS		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

#Headers
HEADERS		:= -I ./include

#Colors
COLOR_INFO = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		@$(CC) $(OBJS) $(HEADERS) -o $(NAME) -lreadline

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) && printf "$(COLOR_INFO)Compiling: $(notdir $<)$(COLOR_RESET)\t\t"
		@sleep 0.25
		@printf "✅\n"

clean:
		@printf "$(COLOR_INFO)Cleaning as fast as I can$(COLOR_RESET)\t"
		@$(CLEAN) $(OBJS_DIR)
		@sleep 0.25
		@printf "✅\n"

fclean: clean
		@printf "$(COLOR_INFO)Deleting $(NAME)$(COLOR_RESET)\t\t"
		@$(CLEAN) $(NAME)
		@sleep 0.25
		@printf "✅\n"

re: fclean clean all

.PHONY: all, clean, fclean, re