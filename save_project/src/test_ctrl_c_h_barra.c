/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ctrl_c_h_barra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:16:33 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/06 17:39:26 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "../inc/libft/libft.h"

void	handle_signal(int sig)
{
	if (sig == 2)
		printf("\nctrl c\n");
	else if (sig == 3)
		printf("\nctrl BARRA\n");
	exit(0);
}

int	main(int ac, char **av, char **ev)
{
	char **argv;
	
	argv = (char **)malloc(sizeof(char *) * 3);
/* 	argv[0] = "\"echo\"";
	argv[1] = "-l";
	argv[2] = "-a"; */
	argv[0] = "-l";
	argv[1] = "-a";
	(void)(ac);
	(void)(av);
	if (execve("/bin/echo", argv, ev) < 0)
		printf("fail\n");
	return (0);
}
