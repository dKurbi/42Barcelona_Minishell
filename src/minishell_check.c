/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:29:48 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/10 20:46:56 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//1 - hay error, 0 - bien
int	initial_check(t_msh *msh)
{
	if (!msh->read_line)
		print_error_exit(&msh, ERR_MALLOC);
	if (!ft_strncmp(msh->read_line, "exit", 4) && \
		ft_strlen(msh->read_line) == 4)
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

int	check_command(char *str)
{
	if (str[0] == '.')
	{
		return (0);
		
	}
	else if (str[0] == '/')
	{
		return (0);

	}
	else
	{
		return (0);
	}
	return (0);
}
