# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 14:31:28 by iassambe          #+#    #+#              #
#    Updated: 2023/12/09 15:53:06 by iassambe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFTFLAGS = -Llibft -lft
READLINEFLAGS = -Lreadline -lreadline
DEPFLAGS = -MMD -MP

DIR_SRC = src/
DIR_INC = inc/
DIR_OBJS = objs/
DIR_LIBFT = libft/

MKDIR = mkdir -p
RM = rm
MAKE = make

MINISHELL = inc/minishell.h
LIBFT = libft.a

SRCS = minishell.c teste.c
OBJS = $(addprefix $(DIR_OBJS), $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(LIBFTFLAGS) $(READLINEFLAGS) $(OBJS) -o $(NAME)

$(DIR_OBJS)%.o: $(DIR_SRC)%.c $(MINISHELL) Makefile
	@$(MKDIR) $(DIR_OBJS)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(DIR_LIBFT)

clean:
	@$(MAKE) -C $(DIR_LIBFT) clean
	$(RM) -rf $(DIR_OBJS)

fclean: clean
	@$(MAKE) -C $(DIR_LIBFT) fclean
	$(RM) -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
