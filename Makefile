# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 14:31:28 by iassambe          #+#    #+#              #
#    Updated: 2024/02/14 16:15:32 by dkurcbar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LIBFTFLAGS = -Linc/libft -lft
READLINEFLAGS = -Linc/readline/
MINIFLAGS = -lreadline -lhistory -ltermcap
INCLUDEFLAGS = -Iinc/ -Iinc/libft/ -Iinc/readline/
DEPFLAGS = -MMD -MP

COL_GREEN = \033[0;32m
COL_RESET = \033[0m

DIR_SRC = src/
DIR_INC = inc/
DIR_OBJS = objs/
DIR_LIBFT = inc/libft/
DIR_READLINE = inc/readline/

MKDIR = mkdir -p
RM = rm
MAKE = make
ECHO = echo

LIB_MINISHELL = inc/minishell.h
COMPILED_LIBFT = libft.a
COMPILED_READLINE = inc/readline/libreadline.a

SRCS = 	minishell.c minishell_error.c minishell_struct.c minishell_getter.c \
		minishell_operators.c minishell_quotes.c minishell_lst_line.c \
		minishell_free.c minishell_pipe.c minishell_utils.c ft_split_pipe.c \
		minishell_expand.c minishell_case.c minishell_check.c minishell_utils_2.c \
		minishell_execute.c minishell_check_syntax.c minishell_signal.c \
		minishell_builtin_env.c minishell_exec_redirection.c minishell_heredoc.c \
		minishell_free_str.c minishell_builtin_cd.c minishell_execute_command.c \
		minishell_execute_pipe.c minishell_search.c minishell_builtin_export.c \
		minishell_builtin_exit.c minishell_builtin_pwd.c minishell_builtin_unset.c \
		minishell_builtin_echo.c minishell_builtin_export_2.c \
		minishell_lst_line_quotes.c minishell_builtin_env_utils.c \
		minishell_signal_handle.c minishell_heredoc_utils.c minishell_utils_3.c \
		minishell_execute_pipe_process.c minishell_wait.c minishell_builtin_export_plus.c \
		minishell_check_2.c minishell_shlvl.c

OBJS = $(addprefix $(DIR_OBJS), $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(COMPILED_LIBFT) $(COMPILED_READLINE) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(DEPFLAGS) $(LIBFTFLAGS) $(READLINEFLAGS) $(MINIFLAGS) -o $(NAME)
	@$(ECHO) "Minishell $(COL_GREEN)Compiled!$(COL_RESET)"

$(DIR_OBJS)%.o: $(DIR_SRC)%.c $(LIB_MINISHELL) Makefile
	@$(MKDIR) $(DIR_OBJS)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDEFLAGS) -c $< -o $@

$(COMPILED_LIBFT):
	$(MAKE) -C $(DIR_LIBFT) bonus

.isconfig :
	touch $@
	cd inc/readline/ && ./configure

config_readline: .isconfig

configure: config_readline

configure_readline: config_readline

config: config_readline

$(COMPILED_READLINE): configure_readline
	$(MAKE) -C $(DIR_READLINE)

clean:
	$(MAKE) -C $(DIR_LIBFT) clean
	$(MAKE) -C $(DIR_READLINE) clean
	$(RM) -rf $(DIR_OBJS)

fclean: clean
	$(RM) -f .isconfig
	$(MAKE) -C $(DIR_LIBFT) fclean
	$(RM) -f $(NAME)

re: fclean all

r: re

norminette:
	norminette inc/libft/*.c inc/libft/*.h inc/minishell.h src/ft* src/minishell*

-include $(DEPS)

.PHONY: all clean fclean re
