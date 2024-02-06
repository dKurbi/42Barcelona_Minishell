/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:39:06 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/06 09:51:15 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_heredoc_pipe(t_msh *msh)
{
	t_pipe	*copy_pipe;
	int		heredoc_status;

	heredoc_status = 0;
	copy_pipe = msh->lst_pipe;
	while (copy_pipe)
	{
		heredoc_status = check_heredoc(msh, copy_pipe->lst_line);
		if (heredoc_status)
			return (heredoc_status);
		copy_pipe->fd_heredoc[0] = dup(msh->exec.fd_here_doc[0]);
		ft_close(&msh->exec.fd_here_doc[0]);
		copy_pipe = copy_pipe->next;
	}
	return (heredoc_status);
}
