/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:53:03 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/15 00:13:48 by iassambe         ###   ########.fr       */
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
	char **argv;
	char	*str = "/bin/cd";

	argv = (char **)malloc(sizeof(char *) * 3);
	printf("lol\n");
	argv[0] = str;
	argv[1] = "..";
	argv[2] = NULL;
	chdir("..");
	//execve(str, argv, NULL);
}