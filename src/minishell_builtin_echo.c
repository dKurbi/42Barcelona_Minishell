/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_echo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:03:05 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/16 15:54:53 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_echo_loop(t_msh *msh, int i)
{
	while (msh->exec.exec_arg[i])
	{
		if (msh->exec.exec_arg[i + 1] == NULL)
			printf("%s", msh->exec.exec_arg[i]);
		else
			printf("%s ", msh->exec.exec_arg[i]);
		i++;
	}
}

int	builtin_echo(t_msh *msh)
{
	int		i;
	int		flag_status;

	flag_status = 0;
	i = 1;
	if (msh->exec.exec_arg[1] && !ft_strncmp(msh->exec.exec_arg[1], "-n", 2) \
	&& ft_strlen(msh->exec.exec_arg[1]) == 2)
	{
		flag_status = 1;
		i++;
	}
	builtin_echo_loop(msh, i);
	if (flag_status == 0)
		printf("\n");
	return (0);
}
