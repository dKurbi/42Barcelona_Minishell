/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:05:26 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/12 18:32:44 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

unsigned long long	ft_atoull(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	num;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) && str[i])
		i++;
	if (str[i] == 45)
	{
		sign = -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	num = sign * num;
	return (num);
}

//0 - numeric required
//1 - good
int	builtin_exit_if_num(char *str)
{
	int	i;

	i = 0;
	if (check_ifempty_str(str) || ft_atoull(str) > MAX_EXIT)
		return (0);
	if ((str[i] == '+' || str[i] == '-') && str[i + 1] == '\0')
		return (0);
	else if ((str[i] == '+' || str[i] == '-') && str[i + 1] != '\0')
		i++;
	while (str[i])
	{
		if (str[i] != ' ' && ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit_make_status(t_msh *msh, int i)
{
	int	status;

	status = ft_atoi(msh->exec.exec_arg[i]);
	free_msh(&msh);
	return (status);
}

//exit: can have options
int	builtin_exit(t_msh *msh)
{
	int	status;

	if (msh->lst_pipe != NULL)
		return (0);
	printf("exit\n");
	if (!msh->exec.exec_arg[1])
	{
		free_msh(&msh);
		exit(EXIT_SUCCESS);
	}
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
	status = builtin_exit_make_status(msh, 1);
	exit(status);
	return (0);
}
