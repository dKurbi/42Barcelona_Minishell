# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 22:43:20 by iassambe          #+#    #+#              #
#    Updated: 2023/10/19 19:51:20 by iassambe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUSNAME = $(NAME)

CC = cc
CFLAGS = -Wall -Wextra -Werror

DIRINC = inc/
DIRSRCS = srcs/
DIRLIBFT = libft/
DIROBJS = objs/

DIRBONUSINC = bonus_inc/
DIRBONUSSRCS = bonus_srcs/
DIRBONUSOBJS = bonus_objs/

LIBFTDONENODIR = libft.a
LIBFTDONE = $(DIRLIBFT)libft.a
PIPEXLIB = $(DIRINC)pipex.h
BONUSPIPEXLIB = $(DIRBONUSINC)pipex_bonus.h

RM = rm
MKDIR = mkdir
MAKE = make
CMDTOUCH = touch

SRCS = pipex.c pipex_utils.c utils.c path_and_cmd.c handler.c
BONUS_SRCS = pipex_bonus.c pipex_utils_bonus.c utils_bonus.c path_and_cmd_bonus.c handler_bonus.c

OBJS = $(addprefix $(DIROBJS), $(SRCS:.c=.o))
BONUSOBJS = $(addprefix $(DIRBONUSOBJS), $(BONUS_SRCS:.c=.o))

all: $(NAME)

$(NAME): clean_bonus $(LIBFTDONENODIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFTDONE) -o $(NAME)

$(DIROBJS)%.o: $(DIRSRCS)%.c $(PIPEXLIB)
	@$(MKDIR) -p $(DIROBJS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFTDONENODIR):
	$(MAKE) -C $(DIRLIBFT)

bonus: clean_mandatory $(LIBFTDONENODIR) $(BONUSOBJS)
	@$(CC) $(CFLAGS) $(BONUSOBJS) $(LIBFTDONE) -o $(BONUSNAME)

$(DIRBONUSOBJS)%.o: $(DIRBONUSSRCS)%.c $(BONUSPIPEXLIB)
	@$(MKDIR) -p $(DIRBONUSOBJS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(DIRLIBFT) clean
	$(RM) -rf $(DIROBJS)
	$(RM) -rf $(DIRBONUSOBJS)

fclean: clean
	$(MAKE) -C $(DIRLIBFT) fclean
	$(RM) -f $(NAME)
	$(RM) -f $(BONUSNAME)

re: fclean all

re_bonus: fclean bonus

clean_mandatory:
	@$(RM) -rf $(DIROBJS)
	@$(RM) -f $(NAME)

clean_bonus:
	@$(RM) -rf $(DIRBONUSOBJS)
	@$(RM) -f $(BONUSNAME)

touchfiles:
	$(CMDTOUCH) infile
	$(CMDTOUCH) outfile
	@echo "test \n infile\nline3\n\nline5\nline final!!!" > infile

untouchfiles:
	$(RM) -f infile
	$(RM) -f outfile

norminette_without_libft:
	@norminette srcs/* inc/* bonus_inc/*.h bonus_srcs/*.c

.PHONY: all clean fclean re
