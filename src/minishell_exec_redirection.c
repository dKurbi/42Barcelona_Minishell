/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:27:14 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/10 03:38:55 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <errno.h>

void	input_redir(t_msh *msh, t_line *copy)
{
	int	fd;

	(void)(msh);
	if ((copy->next) && check_file(copy->next->str))
		return ;
	fd = open(copy->next->str, O_RDONLY, 0644);
	if (fd < 0)
	{
		print_perror(copy->next->str);
		return ;
    }
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	output_redir(t_msh *msh, t_line *copy)
{
	int	fd;

	(void)(msh);
	fd = open(copy->next->str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_perror(copy->next->str);
		return ;
    }
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void 	append_redir(t_msh *msh, t_line *copy)
{
	int	fd;

	(void)(msh);
	fd = open(copy->next->str, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		print_perror(copy->next->str);
		return ;
    }
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
void 	write_herdoc(t_msh *msh, t_line *copy)
{
	char *line;
	
	line = NULL;
	if (pipe(msh->exec.fd_here_doc) == -1)
		print_error_exit(&msh, ERR_PIPE);
	line = readline("> ");
	while (ft_strncmp(line, copy->next->str, ft_strlen(copy->next->str)) \
			|| ft_strlen(line) != ft_strlen(copy->next->str))
	{
		ft_putstr_fd(line, msh->exec.fd_here_doc[0]);
		free_str(&line);
		line = readline("> ");
	}
	free_str(&line);
	close (msh->exec.fd_here_doc[0]);
	copy->fd = dup(msh->exec.fd_here_doc[1]);
}
void check_heredoc(t_msh *msh)
{
	t_line *line_copy;
	
	line_copy = msh->lst_line;
	while(line_copy)
	{
		if (line_copy->type == TYPE_HDC)
			write_herdoc(msh, line_copy);
		line_copy = line_copy->next;
	}
}
void heredoc_redir(t_msh *msh, t_line *copy)
{
	(void)(msh);
	dup2(copy->fd, STDIN_FILENO);
	close(copy->fd);
}

void	control_redirection(t_msh *msh)
{
 	t_line	*copy_line;
	
	msh->exec.fd_stdin = dup(STDIN_FILENO);
	msh->exec.fd_stdout = dup (STDOUT_FILENO);
	copy_line = msh->lst_line;
	check_heredoc(msh);
	while (copy_line)
	{
		if (copy_line->type == TYPE_OPUT_RED)
			output_redir(msh, copy_line);
		else if (copy_line->type == TYPE_IPUT_RED)
			input_redir(msh, copy_line);
		else if (copy_line->type == TYPE_APND)
			append_redir(msh, copy_line);
		else if (copy_line->type == TYPE_HDC)
			heredoc_redir(msh, copy_line);
		copy_line = copy_line->next;
	}	 
}
void restore_redirection(t_msh *msh)
{
	dup2(msh->exec.fd_stdout, STDOUT_FILENO);
	dup2(msh->exec.fd_stdin, STDIN_FILENO);
}
