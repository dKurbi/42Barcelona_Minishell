/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:53:11 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/03 18:22:13 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

void	execute_builtin(t_msh *msh, int if_pipe_mode)
{
	if (control_redirection(msh))
	{
		g_exit_status = 1;
		dup2(msh->exec.fd_stdin, STDIN_FILENO);
		dup2(msh->exec.fd_stdout, STDOUT_FILENO);
		ft_close(&msh->exec.fd_stdin);
		ft_close(&msh->exec.fd_stdout);
		return ;
	}
	if (!strncmp(msh->exec.exec_arg[0], "echo", 4))
		g_exit_status = builtin_echo(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "cd", 2))
		g_exit_status = builtin_cd(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "pwd", 3))
		g_exit_status = builtin_pwd(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "export", 6))
		g_exit_status = builtin_export(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "unset", 5))
		g_exit_status = builtin_unset(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "env", 3))
		g_exit_status = builtin_env(msh);
	else if (!strncmp(msh->exec.exec_arg[0], "exit", 4))
		g_exit_status = builtin_exit(msh);
	if (if_pipe_mode >= 1)
		exit(g_exit_status);
}

//ejecutar los comandos ejemplo: "ls -la"
void	execution_line(t_msh *msh)
{
	signal_control_block(msh);
	g_exit_status = check_heredoc(msh, msh->lst_line);
	if (g_exit_status > 0)
		return ;
	msh->exec.exec_arg = get_exec_argv(msh, msh->lst_line);
	execute_cmd(msh);
	restore_redirection(msh);
	free_double_str(&msh->exec.exec_arg);
}

//ejecutar los comandos ejemplo: "ls -la | wc -l"
void	execution_pipes(t_msh *msh)
{
	t_pipe	*copy_pipe;

	signal_control_block(msh);
	copy_pipe = msh->lst_pipe;
	g_exit_status = check_heredoc_pipe(msh);
	if (g_exit_status >= 1)
		return ;
	while (copy_pipe->next)
	{
		if (pipe(msh->exec.pip) < 0)
			print_error_exit(&msh, ERR_PIPE);
		msh->exec.proc = fork();
		if (msh->exec.proc < 0)
			print_error_exit(&msh, ERR_FORK);
		if (msh->exec.proc == 0)
		{
			signal_control_exec(msh);
			execute_child_pipe(msh, copy_pipe);
			if (copy_pipe->next == NULL)
				execute_child_pipe_last(msh, copy_pipe);//siguente
		}
		change_int_arr(msh->exec.old_pip, msh->exec.pip[0], msh->exec.pip[1]);
		ft_close(&msh->exec.pip[0]);
		ft_close(&msh->exec.pip[1]);
		dup2(msh->exec.old_pip[0], STDOUT_FILENO);
		copy_pipe = copy_pipe->next;
	}
	wait_process(msh, msh->exec.proc, msh->exec.num_commands);
	g_exit_status = msh->exit_status;
	restore_redirection(msh);
}

//luego para executing
void	execution(t_msh *msh)
{
	if (check_ifempty_str(msh->read_line) && msh->read_line[0] != '\0')
		return ;
	if (msh->lst_pipe != NULL)
	{
		msh->exec.num_commands = calculate_len_lst_pipe(msh->lst_pipe);
		execution_pipes(msh);
	}
	else
		execution_line(msh);
}
