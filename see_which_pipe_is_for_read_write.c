/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   see_which_pipe_is_for_read_write.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:39:48 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/01 16:40:17 by iassambe         ###   ########.fr       */
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

int	main(void)
{	
	int	pip[2];
	char	reado[20];

	if (pipe(pip) < 0)
		exit(1);

	//incorrecte totalmente
/* 	if (write(pip[0], "pip\n", 4) < 0)
		printf("u NO at writing pip[0]\n");
	if (read(pip[1], reado, 4) < 0)
		printf("u NO at READING pip[1]\n"); */

	//correcto totalmente
	if (write(pip[1], "lox\n", 4) < 0)
		printf("u NO at writing pip[1]\n");
	if (read(pip[0], reado, 4) < 0)
		printf("u NO at READING pip[0]\n");

	//incorrecte
/* 	if (write(pip[1], "lox\n", 4) < 0)
		printf("u NO at writing pip[1]\n");
	if (read(pip[1], reado, 4) < 0)
		printf("u NO at READING pip[1]\n"); */
	
	reado[5] = '\0';
	printf("$READO - %s\n", reado);
	close(pip[0]);
	close(pip[1]);
	return (0);
}