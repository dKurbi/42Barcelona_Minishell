# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 14:31:28 by iassambe          #+#    #+#              #
#    Updated: 2023/12/13 16:51:27 by dkurcbar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIBFTFLAGS = -Linc/libft -lft
READLINEFLAGS = -L$(HOME)/.brew/opt/readline/lib -lreadline
BREWFLAGS = -I$(HOME)/.brew/opt/readline/include
DEPFLAGS = -MMD -MP

DIR_SRC = src/
DIR_INC = inc/
DIR_OBJS = objs/
DIR_LIBFT = inc/libft/

MKDIR = mkdir -p
RM = rm
MAKE = make

MINISHELL = inc/minishell.h
LIBFT = libft.a

SRCS = minishell.c minishell_error.c minishell_struct.c minishell_parser.c \
		minishell_getter.c minishell_quotes.c minishell_line_st.c \
		minishell_free.c
OBJS = $(addprefix $(DIR_OBJS), $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(BREWFLAGS) $(LIBFTFLAGS) $(READLINEFLAGS) $(OBJS) -o $(NAME)

$(DIR_OBJS)%.o: $(DIR_SRC)%.c $(MINISHELL) Makefile
	@$(MKDIR) $(DIR_OBJS)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(BREWFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(DIR_LIBFT) bonus

clean:
	@$(MAKE) -C $(DIR_LIBFT) clean
	$(RM) -rf $(DIR_OBJS)

fclean: clean
	@$(MAKE) -C $(DIR_LIBFT) fclean
	$(RM) -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
