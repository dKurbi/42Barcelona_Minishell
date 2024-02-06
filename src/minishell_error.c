/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:59:06 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/06 19:13:33 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//exit with printing 1 error message
void	print_error_exit(t_msh **msh, char *s_err)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, s_err, ft_strlen(s_err));
	if (*msh != NULL)
		free_msh(msh);
	*msh = NULL;
	exit(EXIT_FAILURE);
}

//only write error message
void	print_warning(char *s_warn)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, s_warn, ft_strlen(s_warn));
}

//only write 2 error messages
void	print_warning_with_arg(char *file, char *s_warn)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, file, ft_strlen(file));
	write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, s_warn, ft_strlen(s_warn));
}

//print error using perror() function
void	print_perror(char *s_err)
{
	write(STDERR_FILENO, STR_MINISHELL, ft_strlen(STR_MINISHELL));
	perror(s_err);
}

//print error using perror() function and with addictional arg
void	print_perror_with_arg(char *cmd, char *file)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", ft_strlen(": "));
	perror(file);
}
