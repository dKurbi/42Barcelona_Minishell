/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:59:06 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/25 19:35:53 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//salimos
void	print_error_exit(t_msh **msh, char *s_err)
{
/* 	int	exit_status;

	exit_status = (*msh)->exit_status; */
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, s_err, ft_strlen(s_err));
	if (*msh != NULL)
		free_msh(msh);
	*msh = NULL;
	//exit(exit_status);
	exit(EXIT_FAILURE);
}

//no salimos
void	print_warning(char *s_warn)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, s_warn, ft_strlen(s_warn));
}