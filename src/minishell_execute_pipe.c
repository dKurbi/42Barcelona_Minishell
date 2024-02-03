/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:07:32 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/03 03:36:29 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

void	execute_cmd_pipe(t_msh *msh)
{
	signal_control_block(msh);
	if (check_ifbuiltin(msh->exec.exec_arg[0]))
		execute_builtin(msh, EXECUTE_PIPE);
	/* else
	{
		if (msh->exec.fd_here_doc[0] != -1)
			ft_close(msh->exec.fd_here_doc[0]);
	} */
	if (control_redirection(msh))
	{
		ft_close(msh->exec.fd_stdin);
		ft_close(msh->exec.fd_stdout);
		ft_close(msh->exec.pip[0]);
		ft_close(msh->exec.pip[1]);
		g_exit_status = 1;
		exit(g_exit_status);
	}
	signal_control_exec(msh);
	if (execute_child_argv(&msh))
		exit_free_child(msh, 1);
	msh->exec.path = search_path(msh);
	if (!msh->exec.path)
		exit_free_child(msh, 127);
	execute_check_command_and_execve(msh);
	exit_free_child(msh, g_exit_status);
}

void	restore_redirection_pipe(t_msh *msh)
{
	dup2(msh->exec.fd_stdout, STDOUT_FILENO);
	dup2(msh->exec.fd_stdin, STDIN_FILENO);
	ft_close(msh->exec.fd_stdout);
	ft_close(msh->exec.fd_stdin);
}

void	execute_child_pipe(t_msh *msh, t_pipe *lst_pipe)
{
	signal_control_block(msh);
	dup2(msh->exec.pip[0], STDIN_FILENO);
	ft_close(msh->exec.pip[0]);
	g_exit_status = check_heredoc(msh, lst_pipe->lst_line);
	if (g_exit_status > 0)
		//return ; //if exit doesn't work well
		exit(g_exit_status);
	msh->exec.exec_arg = get_exec_argv(msh, lst_pipe->lst_line);
	execute_cmd_pipe(msh);
	free_double_str(&msh->exec.exec_arg);
	restore_redirection_pipe(msh);
}
