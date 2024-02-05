/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:39:06 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/05 15:50:15 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_heredoc_pipe(t_msh *msh)
{
	t_pipe *copy_pipe;
	int		heredoc_status;
	//int i = 1;

	heredoc_status = 0;
	copy_pipe = msh->lst_pipe;
	while (copy_pipe)
	{
		//printf("check herredoc %d\n", i++);
		heredoc_status = check_heredoc(msh, copy_pipe->lst_line);
		if (heredoc_status)
			return (heredoc_status);
		copy_pipe->fd_heredoc[0] = dup(msh->exec.fd_here_doc[0]);
		//copy_pipe->fd_heredoc[1] = dup(msh->exec.fd_here_doc[1]);
		ft_close(&msh->exec.fd_here_doc[0]);
		//ft_close(&msh->exec.fd_here_doc[1]);
		copy_pipe = copy_pipe->next;
	}
	
	return (heredoc_status);
/* 	t_line	*line_copy;
	int		heredoc_status;

	heredoc_status = 0;
	line_copy = lst_line;
	while (line_copy)
	{
		if (line_copy->type == TYPE_HDC)
		{
			heredoc_status = fork_write_heredoc(msh, line_copy);
			if (heredoc_status > 0)
				return (heredoc_status);
		}
		line_copy = line_copy->next;
	}
	return (heredoc_status); */
	
}