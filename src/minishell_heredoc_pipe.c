/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:39:06 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/05 19:15:40 by iassambe         ###   ########.fr       */
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
		printf("check_heredoc_pipe: el fd msh->exec.fd_here_doc[0] = %d\n",msh->exec.fd_here_doc[0]);

		copy_pipe->fd_heredoc[0] = dup(msh->exec.fd_here_doc[0]);
		printf("check_heredoc_pipe: el fd copy_pipe->fd_heredoc[0] = %d\n",copy_pipe->fd_heredoc[0]);
		//copy_pipe->fd_heredoc[1] = dup(msh->exec.fd_here_doc[1]);
		ft_close(&msh->exec.fd_here_doc[0]);
		//ft_close(&msh->exec.fd_here_doc[1]);
		copy_pipe = copy_pipe->next;
	}
	
	return (heredoc_status);
}