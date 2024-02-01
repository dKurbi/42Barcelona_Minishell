/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:07:32 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/01 19:53:21 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_cmd_pipe(t_msh *msh)
{
	signal_control_block(msh);
	if (check_ifbuiltin(msh->exec.exec_arg[0]))
	{
		execute_builtin(msh, EXECUTE_COMMAND);
		return ;
	}
	if (pipe(msh->exec.pip) < 0)
		print_error_exit(&msh, ERR_PIPE);
	msh->exec.proc = fork();
	if (msh->exec.proc < 0)
		print_error_exit(&msh, ERR_FORK);
	if (msh->exec.proc == 0)
	{
		signal_control_exec(msh);
		execute_child(msh);
	}
	else
	{
		if (msh->exec.fd_here_doc[0] != -1)
			ft_close(msh->exec.fd_here_doc[0]);
	}
	ft_close(msh->exec.pip[0]);
	ft_close(msh->exec.pip[1]);
	wait_process(msh, msh->exec.proc, ONE_COMMAND);
	g_exit_status = msh->exit_status; */
}

void	execute_child_pipe(t_msh *msh, t_pipe *lst_pipe)
{
	signal_control_block(msh);
	g_exit_status = check_heredoc(msh, lst_pipe->lst_line);
	if (g_exit_status > 0)
		//return ;
		exit(g_exit_status);
	msh->exec.exec_arg = get_exec_argv(msh, lst_pipe->lst_line);
	execute_cmd_pipe(msh);
	restore_redirection(msh);
	free_double_str(&msh->exec.exec_arg);
}
