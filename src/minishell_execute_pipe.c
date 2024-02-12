/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:07:32 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/12 19:21:32 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

int	control_redirection_pipes(t_msh *msh)
{
	t_line	*copy_line;
	int		status;

	status = 0;
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

void	execute_child_pipe(t_msh *msh)
{
	if (check_ifbuiltin(msh->exec.exec_arg[0]))
		execute_builtin_pipes(msh);
	if (control_redirection_pipes(msh))
	{
		ft_close(&msh->exec.fd_stdin);
		ft_close(&msh->exec.fd_stdout);
		ft_close(&msh->exec.pip[0]);
		ft_close(&msh->exec.pip[1]);
		exit(1);
	}
	signal_control_exec(msh);
	if (execute_child_argv(&msh))
		exit_free_child(msh, 0);
	msh->exec.path = search_path(msh);
	execute_check_command_and_execve(msh);
	exit_free_child(msh, g_exit_status);
}

void	execute_cmd_pipe(t_msh *msh)
{
	signal_control_block();
	if (pipe(msh->exec.pip) < 0)
		print_error_exit(&msh, ERR_PIPE);
	msh->exec.proc = fork();
	if (msh->exec.proc < 0)
		print_error_exit(&msh, ERR_FORK);
	if (msh->exec.proc == 0)
	{
		close_int_arr(msh->exec.even_pip);
		close_int_arr(msh->exec.odd_pip);
		signal_control_exec(msh);
		execute_child_pipe(msh);
	}
	else
	{
		if (msh->exec.fd_here_doc[0] != -1)
			ft_close(&msh->exec.fd_here_doc[0]);
	}
	ft_close(&msh->exec.pip[0]);
	ft_close(&msh->exec.pip[1]);
}

//execute builtins for pipes
void	execute_builtin_pipes(t_msh *msh)
{
	int	status;

	status = 0;
	if (control_redirection_pipes(msh))
	{
		g_exit_status = 1;
		dup2(msh->exec.fd_stdin, STDIN_FILENO);
		dup2(msh->exec.fd_stdout, STDOUT_FILENO);
		ft_close(&msh->exec.fd_stdin);
		ft_close(&msh->exec.fd_stdout);
		exit_free_child(msh, 1);
	}
	if (!strncmp(msh->exec.exec_arg[0], "echo", 4))
		status = builtin_echo(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "cd", 2))
		status = builtin_cd(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "pwd", 3))
		status = builtin_pwd(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "export", 6))
		status = builtin_export(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "unset", 5))
		status = builtin_unset(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "env", 3))
		status = builtin_env(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "exit", 4))
		status = builtin_exit(msh);
	exit_free_child(msh, status);
}

//execute pipes (ls | cat)
void	execution_pipes(t_msh *msh)
{
	t_pipe	*copy_pipe;
	int		i;

	signal_control_block();
	g_exit_status = check_heredoc_pipe(msh);
	if (g_exit_status > 0)
		return ;
	i = 0;
	copy_pipe = msh->lst_pipe;
	msh->exec.fd_stdin = dup(STDIN_FILENO);
	msh->exec.fd_stdout = dup(STDOUT_FILENO);
	while (copy_pipe)
	{
		execution_pipes_prepare(msh, i, copy_pipe);
		execute_cmd_pipe(msh);
		execution_pipes_prepare_next(msh, &i);
		copy_pipe = copy_pipe->next;
	}
	close_int_arr(msh->exec.odd_pip);
	close_int_arr(msh->exec.even_pip);
	restore_redirection(msh);
	wait_process(msh, msh->exec.proc, i + 1);
	g_exit_status = msh->exit_status;
}
