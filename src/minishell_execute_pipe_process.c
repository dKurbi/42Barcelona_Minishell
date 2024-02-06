/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute_pipe_process.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:17:26 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/06 19:26:09 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

//prepare before executing pipes
void	execution_pipes_prepare(t_msh *msh, int i, t_pipe *copy_pipe)
{
	execution_pipes_decide_dup(msh, i, copy_pipe);
	msh->lst_line = ft_lstdup(copy_pipe->lst_line);
	msh->exec.fd_here_doc[0] = dup(copy_pipe->fd_heredoc[0]);
	msh->exec.exec_arg = get_exec_argv(msh, msh->lst_line);
}

//free and close before next piping
void	execution_pipes_prepare_next(t_msh *msh, int *i)
{
	free_lst_line(&msh->lst_line);
	free_double_str(&msh->exec.exec_arg);
	if (*i % 2 == 1)
		ft_close(&msh->exec.even_pip[0]);
	else if (*i > 0 && *i % 2 == 0)
		ft_close(&msh->exec.odd_pip[0]);
	(*i)++;
}

void	execution_pipes_decide_dup_last(t_msh *msh, int i, t_pipe *copy_pipe)
{
	if (i % 2 == 0 && !copy_pipe->next)
	{
		ft_close(&msh->exec.odd_pip[1]);
		if (pipe(msh->exec.even_pip) < 0)
			print_error_exit(&msh, ERR_PIPE);
		dup2(msh->exec.odd_pip[0], STDIN_FILENO);
		dup2(msh->exec.fd_stdout, STDOUT_FILENO);
		ft_close(&msh->exec.odd_pip[0]);
		ft_close(&msh->exec.fd_stdout);
	}
}

void	execution_pipes_decide_dup_else(t_msh *msh, int i, t_pipe *copy_pipe)
{
	if (i > 0 && i % 2 == 0 && copy_pipe->next)
	{
		ft_close(&msh->exec.odd_pip[1]);
		if (pipe(msh->exec.even_pip) < 0)
			print_error_exit(&msh, ERR_PIPE);
		dup2(msh->exec.odd_pip[0], STDIN_FILENO);
		dup2(msh->exec.even_pip[1], STDOUT_FILENO);
		ft_close(&msh->exec.odd_pip[0]);
		ft_close(&msh->exec.even_pip[1]);
	}
	else if (i % 2 == 1 && !copy_pipe->next)
	{
		ft_close(&msh->exec.even_pip[1]);
		if (pipe(msh->exec.odd_pip) < 0)
			print_error_exit(&msh, ERR_PIPE);
		dup2(msh->exec.even_pip[0], STDIN_FILENO);
		dup2(msh->exec.fd_stdout, STDOUT_FILENO);
		ft_close(&msh->exec.even_pip[0]);
		ft_close(&msh->exec.fd_stdout);
	}
	else
		execution_pipes_decide_dup_last(msh, i, copy_pipe);
}

//duplicate, deciding the position of pipe
void	execution_pipes_decide_dup(t_msh *msh, int i, t_pipe *copy_pipe)
{
	if (i == 0)
	{
		if (pipe(msh->exec.even_pip) < 0)
			print_error_exit(&msh, ERR_PIPE);
		dup2(msh->exec.even_pip[1], STDOUT_FILENO);
		ft_close(&msh->exec.even_pip[1]);
	}
	else if (i % 2 == 1 && copy_pipe->next)
	{
		ft_close(&msh->exec.even_pip[1]);
		if (pipe(msh->exec.odd_pip) < 0)
			print_error_exit(&msh, ERR_PIPE);
		dup2(msh->exec.even_pip[0], STDIN_FILENO);
		dup2(msh->exec.odd_pip[1], STDOUT_FILENO);
		ft_close(&msh->exec.even_pip[0]);
		ft_close(&msh->exec.odd_pip[1]);
	}
	else
		execution_pipes_decide_dup_else(msh, i, copy_pipe);
}
