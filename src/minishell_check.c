/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:29:48 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/12 15:38:10 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//1 - error, 0 - good
int	initial_check(t_msh *msh)
{
	if (check_isvalid(msh))
		print_error_exit(&msh, ERR_NO_ASCII);
	if (!msh->read_line || (!ft_strncmp(msh->read_line, "exit", 4) && \
		ft_strlen(msh->read_line) == 4))
	{
		ft_printf("exit\n");
		return (1);
	}
	if (msh->read_line[0] == '\0' || check_ifempty_str(msh->read_line) == 1)
		return (0);
	else
		add_history(msh->read_line);
	return (0);
}

//1 - file isnt OK, 0 - file OK
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
	if (!str)
		return (1);
	if (access(str, F_OK) == 0)
	{
		if (access(str, X_OK) < 0)
			return (1);
	}
	else
		return (1);
	return (0);
}

//0 - not builtin, 1 - is builtin
int	check_ifbuiltin(char *str)
{
	if (!str)
		return (0);
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
//check for + : a+a= - invalid
//returns 1 if is bad, and 0 if is ok
int	check_var_equal(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (check_ifempty_str(str))
		return (1);
	else if (str[0] == '=' || ft_isdigit(str[0]) || str[0] == '+')
		return (1);
	else
	{
		len = ft_strlen(str);
		while (str[i] && str[i] != '=')
		{
			if (!ft_isalnum(str[i]))
			{
				if (str[i] == '+' && (i == len - 2))
					return (0);
				else
					return (1);
			}
			i++;
		}
	}
	return (0);
}
