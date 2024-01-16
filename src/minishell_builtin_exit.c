/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:05:26 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/16 17:21:03 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_exit_if_num(char *str)
{
	int	i;

	i = 0;
	if (check_ifempty_str(str))
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_msh *msh)
{
	int	status;

	printf("exit\n");
	if (msh->exec.exec_arg[1] && msh->exec.exec_arg[2])
	{
		print_warning_with_arg("exit", ERR_TOO_MANY);
		return (1);
	}
	else if (!builtin_exit_if_num(msh->exec.exec_arg[1]))
	{
		print_warning_with_3_arg("exit", msh->exec.exec_arg[1], ERR_NUMERIC);
		free_msh(&msh);
		exit(255);
	}
	status = ft_atoi(msh->exec.exec_arg[1]);
	if (status < 0)
		status = 256 - status;
	free_msh(&msh);
	exit(status);
	return (0);
}
