/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:59:06 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/05 16:30:17 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//salimos
//HE PUESTO int exit_status para salir bien, pero no entiendo como hacerlo bien
void	print_error_exit(t_msh **msh, char *s_err)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, s_err, ft_strlen(s_err));
	if (*msh != NULL)
		free_msh(msh);
	*msh = NULL;
	exit(EXIT_FAILURE);
}

//no salimos pero escribimos mensaje
void	print_warning(char *s_warn)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, s_warn, ft_strlen(s_warn));
}

void	print_warning_with_arg(char *file, char *s_warn)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, file, ft_strlen(file));
	write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, s_warn, ft_strlen(s_warn));
}

void	print_perror(char *s_err)
{
	write(STDOUT_FILENO, STR_MINISHELL, ft_strlen(STR_MINISHELL));
	perror(s_err);
}

void	print_perror_with_arg(char *cmd, char *file)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDOUT_FILENO, cmd, ft_strlen(cmd));
	write(STDOUT_FILENO, ": ", ft_strlen(": "));
	perror(file);
}
