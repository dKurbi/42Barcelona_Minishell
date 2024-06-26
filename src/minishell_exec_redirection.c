/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/06 19:16:36 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <errno.h>

int	input_redir(t_msh *msh, t_line *copy)
{
	int	fd;

	(void) msh;
	if ((copy->next) && check_file(copy->next->str))
		return (1);
	fd = open(copy->next->str, O_RDONLY, 0644);
	if (fd < 0)
	{
		print_perror(copy->next->str);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	ft_close(&fd);
	return (0);
}

int	output_redir(t_msh *msh, t_line *copy)
{
	int	fd;

	(void)(msh);
	fd = open(copy->next->str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_perror(copy->next->str);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	ft_close(&fd);
	return (0);
}

int	append_redir(t_msh *msh, t_line *copy)
{
	int	fd;

	(void)(msh);
	fd = open(copy->next->str, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		print_perror(copy->next->str);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	ft_close(&fd);
	return (0);
}

//duplacting original STDIN and STDOUT
//if there are redirections - duplicate them as new streams
int	control_redirection(t_msh *msh)
{
	t_line	*copy_line;
	int		status;

	status = 0;
	msh->exec.fd_stdin = dup(STDIN_FILENO);
	msh->exec.fd_stdout = dup(STDOUT_FILENO);
	copy_line = msh->lst_line;
	while (copy_line)
	{
		if (copy_line->type == TYPE_OPUT_RED)
			status = output_redir(msh, copy_line);
		else if (copy_line->type == TYPE_IPUT_RED)
			status = input_redir(msh, copy_line);
		else if (copy_line->type == TYPE_APND)
			status = append_redir(msh, copy_line);
		if (status >= 1)
			return (1);
		if (copy_line->type == TYPE_HDC)
			heredoc_redir(msh);
		copy_line = copy_line->next;
	}
	return (0);
}

//we restore our results to the terminal
void	restore_redirection(t_msh *msh)
{
	dup2(msh->exec.fd_stdout, STDOUT_FILENO);
	dup2(msh->exec.fd_stdin, STDIN_FILENO);
	ft_close(&msh->exec.fd_stdout);
	ft_close(&msh->exec.fd_stdin);
}
