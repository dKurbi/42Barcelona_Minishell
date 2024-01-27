/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:50:51 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/26 16:43:42 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	write_herdoc(t_msh *msh, t_line *copy)
{
	char	*line;

	line = NULL;
	if (msh->exec.fd_here_doc[0] != -1)
		ft_close(msh->exec.fd_here_doc[0]);
	if (pipe(msh->exec.fd_here_doc) == -1)
		print_error_exit(&msh, ERR_PIPE);
	line = readline("> ");
	while (ft_strncmp(line, copy->next->str, ft_strlen(copy->next->str)) \
			|| ft_strlen(line) != ft_strlen(copy->next->str))
	{
		ft_putstr_fd(line, msh->exec.fd_here_doc[1]);
		ft_putchar_fd('\n', msh->exec.fd_here_doc[1]);
		free_str(&line);
		line = readline("> ");
	}
	ft_putchar_fd('\0', msh->exec.fd_here_doc[1]);
	free_str(&line);
	ft_close(msh->exec.fd_here_doc[1]);
	//copy->fd = dup(msh->exec.fd_here_doc[0]);
	//ft_close(msh->exec.fd_here_doc[0]);
}

void	check_heredoc(t_msh *msh)
{
	t_line	*line_copy;

	line_copy = msh->lst_line;
	while (line_copy)
	{
		if (line_copy->type == TYPE_HDC)
			write_herdoc(msh, line_copy);
		line_copy = line_copy->next;
	}
}

void	heredoc_redir(t_msh *msh)
{
	dup2(msh->exec.fd_here_doc[0], STDIN_FILENO);
	ft_close(msh->exec.fd_here_doc[0]);
}
