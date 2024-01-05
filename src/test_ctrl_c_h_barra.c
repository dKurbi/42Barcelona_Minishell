/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ctrl_c_h_barra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:16:33 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/05 19:49:52 by iassambe         ###   ########.fr       */
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

int	main(void)
{
	char	*s;
	sig_t	sigt;

	s = "sig reading";
	sigt = handle_signal;
	printf("%s\n", s);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		printf("yes\n");
	}
	return (0);
}
