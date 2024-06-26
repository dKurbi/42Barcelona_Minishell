/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 02:23:53 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/06 09:53:41 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//int *fd is fd[2]
void	close_int_arr(int *fd)
{
	ft_close(&fd[1]);
	ft_close(&fd[0]);
}

//redirect heredoc to use as stdin (or as <)
void	heredoc_redir(t_msh *msh)
{
	dup2(msh->exec.fd_here_doc[0], STDIN_FILENO);
	ft_close(&msh->exec.fd_here_doc[0]);
}
