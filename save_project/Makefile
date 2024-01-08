# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 14:31:28 by iassambe          #+#    #+#              #
#    Updated: 2024/01/08 19:03:42 by dkurcbar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
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

SRCS = PRINT.c \
		minishell.c minishell_error.c minishell_struct.c minishell_parser.c \
		minishell_getter.c minishell_quotes.c minishell_lst_line.c \
		minishell_free.c minishell_pipe.c minishell_utils.c ft_split_pipe.c minishell_operators.c \
		minishell_expand.c minishell_case.c minishell_check.c minishell_utils_2.c \
		minishell_execute.c minishell_check_syntax.c minishell_signal.c \
		minishell_env.c
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

config_readline:
	cd inc/readline/ && ./configure

configure: config_readline

configure_readline: config_readline

config: config_readline

$(COMPILED_READLINE): #config_readline WARNING: descomentarlo cuando sera evaluacion
	$(MAKE) -C $(DIR_READLINE)

clean:
	$(MAKE) -C $(DIR_LIBFT) clean
	$(MAKE) -C $(DIR_READLINE) clean
	$(RM) -rf $(DIR_OBJS)

fclean: clean
	$(MAKE) -C $(DIR_LIBFT) fclean
	$(RM) -f $(NAME)

re: fclean all

r: re

norminette:
	norminette inc/minishell.h src/ft* src/minishell*

-include $(DEPS)

.PHONY: all clean fclean re
