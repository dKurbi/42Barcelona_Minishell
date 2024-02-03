/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:36:27 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/02 20:01:22 by iassambe         ###   ########.fr       */
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
# include <fcntl.h>

/* void	ft_close(int *fd)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -1;
} */

void	ft_close(int fd)
{
	if (fd >= 0)
		close(fd);
	fd = -1;
}

void	ch(int *pip, int fd1, int fd2)
{
	(void)(pip);
	(void)(fd1);
	(void)(fd2);
}

int	main(void)
{	
	int	fd_in = -1;
	int	fd_out = -1;
	int	fd1 = -1;
	int	fd2 = -1;
	int	fd3 = -1;
	int	fd4 = -1;
	int	pip[2];

	int	i = 0;
	int	max = 5;
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	pip[0] = -1;
	pip[1] = -1;
	printf ("fdin - %d, fdout - %d, fd1 - %d, fd2 - %d, fd3 - %d, fd4 - %d, pip0 - %d, pip1 - %d\n\n", fd_in, fd_out, fd1, fd2, fd3, fd4, pip[0], pip[1]);
	fd1 = open("fddup.txt", O_RDWR);
	fd2 = open("fddup_2.txt", O_RDWR);
	fd3 = open("lol", O_RDONLY);
	fd4 = dup(STDIN_FILENO);
	
	printf ("fdin - %d, fdout - %d, fd1 - %d, fd2 - %d, fd3 - %d, fd4 - %d, pip0 - %d, pip1 - %d\n\n", fd_in, fd_out, fd1, fd2, fd3, fd4, pip[0], pip[1]);

	while (i < max)
	{
		
		i++;
	}
	
	dup2(fd1, STDOUT_FILENO);
	dup2(fd2, STDOUT_FILENO);
	dup2(fd_in, STDOUT_FILENO);

/* 	ft_close(fd1);
	ft_close(fd2);
	ft_close(fd_in); */
	
	fd3 = dup(STDIN_FILENO);
	printf ("fdin - %d, fdout - %d, fd1 - %d, fd2 - %d, fd3 - %d, fd4 - %d, pip0 - %d, pip1 - %d\n\n", fd_in, fd_out, fd1, fd2, fd3, fd4, pip[0], pip[1]);


	dup2(fd1, STDOUT_FILENO);
	dup2(fd2, STDOUT_FILENO);
	dup2(fd_in, STDOUT_FILENO);
	printf ("fdin - %d, fdout - %d, fd1 - %d, fd2 - %d, fd3 - %d, fd4 - %d, pip0 - %d, pip1 - %d\n\n", fd_in, fd_out, fd1, fd2, fd3, fd4, pip[0], pip[1]);

	
/* 	fd_in = dup(STDIN_FILENO);
	fd1 = dup(STDIN_FILENO);
	fd2 = dup(STDOUT_FILENO);
	fd3 = dup(STDOUT_FILENO); */

	dup(STDIN_FILENO);

	dup2(fd_in, STDIN_FILENO);	
	dup2(fd_in, STDIN_FILENO);	
	dup2(fd_in, STDIN_FILENO);	
	dup2(fd_in, STDIN_FILENO);	
	dup2(fd_in, STDIN_FILENO);
	
	
	printf ("fdin - %d, fdout - %d, fd1 - %d, fd2 - %d, fd3 - %d, fd4 - %d, pip0 - %d, pip1 - %d\n\n", fd_in, fd_out, fd1, fd2, fd3, fd4, pip[0], pip[1]);
	
	printf ("RETURNUN!\n");
	printf ("RETURNUN!\n");
	printf ("RETURNUN!\n");
	printf ("RETURNUN!\n");

/* 	ft_close(&fd_in);
	ft_close(&fd_out);
	ft_close(&fd1);
	ft_close(&fd2);
	ft_close(&fd3);
	ft_close(&fd4); */
	
/* 	ft_close(fd_in);
	ft_close(fd_out);
	ft_close(fd1);
	ft_close(fd2);
	ft_close(fd3);
	ft_close(fd4); */

	dup2(fd_out, STDOUT_FILENO);
	//close(fd_out);

	printf ("fdin - %d, fdout - %d, fd1 - %d, fd2 - %d, fd3 - %d, fd4 - %d, pip0 - %d, pip1 - %d\n\n", fd_in, fd_out, fd1, fd2, fd3, fd4, pip[0], pip[1]);
	printf ("FIN!\n");
	printf ("FIN!\n");
	printf ("FIN!\n");
	printf ("FIN!\n");
}