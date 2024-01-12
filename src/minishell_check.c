/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:29:48 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/12 17:39:09 by dkurcbar         ###   ########.fr       */
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
