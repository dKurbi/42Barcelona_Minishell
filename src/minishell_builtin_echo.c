/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_echo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:03:05 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/12 20:04:25 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//return 1 - yes flag
//return -1 - no flag
int	builtin_echo_if_flag(t_msh *msh, int i)
{
	int	i_iter;

	if (!msh->exec.exec_arg[i])
		return (-1);
	i_iter = 1;
	if (msh->exec.exec_arg[i][0] != '-')
		return (-1);
	else if (msh->exec.exec_arg[i][0] == '-' && \
			msh->exec.exec_arg[i][1] == '\0')
		return (-1);
	while (msh->exec.exec_arg[i][i_iter])
	{
		if (msh->exec.exec_arg[i][i_iter] == 'n')
			i_iter++;
		else
			return (-1);
	}
	return (1);
}

//if we have too much -n -nnn
int	builtin_echo_skip_flags(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->exec.exec_arg[++i])
	{
		if (builtin_echo_if_flag(msh, i) < 0)
			return (i);
	}
	return (i);
}

void	builtin_echo_loop(t_msh *msh, int i)
{
	while (msh->exec.exec_arg[i])
	{
		if (msh->exec.exec_arg[i + 1] == NULL)
			write(1, msh->exec.exec_arg[i], ft_strlen(msh->exec.exec_arg[i]));
		else
		{
			write(1, msh->exec.exec_arg[i], ft_strlen(msh->exec.exec_arg[i]));
			write(1, " ", ft_strlen(" "));
		}
		i++;
	}
}

int	builtin_echo(t_msh *msh)
{
	int		i;
	int		flag_status;

	flag_status = 0;
	i = 1;
	if (builtin_echo_if_flag(msh, 1) > 0)
	{
		flag_status = 1;
		i = builtin_echo_skip_flags(msh);
	}
	builtin_echo_loop(msh, i);
	if (flag_status == 0)
		write(STDOUT_FILENO, "\n", ft_strlen("\n"));
	return (0);
}
