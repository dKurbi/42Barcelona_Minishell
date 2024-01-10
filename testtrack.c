/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testtrack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:24:02 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/10 17:32:00 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int	main(void)
{
	int	fd;
	int	fd2;
	int	fd3;

	fd = open("a", O_RDONLY);
	fd2 = open("b", O_RDONLY);
	fd3 = open("c", O_RDONLY);


	if (fd < 0 || fd2 < 0 || fd3 < 0)
	{
		printf("LOL FD-------\n");
		return (1);
	}
	close(fd2);
	printf("%d\n", fd);
	close(fd);
	printf("%d\n", fd3);
	close(fd3);
	return (0);
}
