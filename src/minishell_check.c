/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:29:48 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/21 23:29:32 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//1 - hay error, 0 - bien
int	initial_check(t_msh *msh)
{
	if (!msh->read_line || (!ft_strncmp(msh->read_line, "exit", 4) && \
		ft_strlen(msh->read_line) == 4))
	{
		ft_printf("exit\n");
		return (1);
	}
	if (msh->read_line[0] != '\0')
		add_history(msh->read_line);
	return (0);
}

int	check_file(char *file)
{
	if (access(file, F_OK) < 0)
	{
		print_perror(file);
		return (1);
	}
	if (access(file, R_OK) < 0)
	{
		print_perror(file);
		return (1);
	}
	return (0);
}

//return 1 - invalid, 0 - invalid
int	check_command(char *str)
{
	if (access(str, F_OK) == 0)
	{
		if (access(str, X_OK) < 0)
			return (1);
	}
	else
		return (1);
	return (0);
}

int	check_ifbuiltin(char *str)
{
	if (!strncmp(str, "echo", 4) && ft_strlen(str) == 4)
		return (1);
	else if (!strncmp(str, "cd", 2) && ft_strlen(str) == 2)
		return (1);
	else if (!strncmp(str, "pwd", 3) && ft_strlen(str) == 3)
		return (1);
	else if (!strncmp(str, "export", 6) && ft_strlen(str) == 6)
		return (1);
	else if (!strncmp(str, "unset", 5) && ft_strlen(str) == 5)
		return (1);
	else if (!strncmp(str, "env", 3) && ft_strlen(str) == 3)
		return (1);
	else if (!strncmp(str, "exit", 4) && ft_strlen(str) == 4)
		return (1);
	return (0);
}

//check if = or if ""= or if =STRING
int	check_var_equal(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (1);
	else
	{
		while (str[i] && (str[i] == QUOTE || str[i] == DQUOTE))
			i++;
		if (str[i] == QUOTE || str[i] == DQUOTE)
			return (1);
	}
	return (0);
}
