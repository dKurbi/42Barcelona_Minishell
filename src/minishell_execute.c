/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:53:11 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/06 19:39:23 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

//execute builtin for only command
void	execute_builtin(t_msh *msh)
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
}

//execute only command, for example: "ls -la"
void	execution_line(t_msh *msh)
{
	signal_control_block();
	g_exit_status = check_heredoc(msh, msh->lst_line);
	if (g_exit_status > 0)
		return ;
	msh->exec.exec_arg = get_exec_argv(msh, msh->lst_line);
	if (!msh->exec.exec_arg)
		print_error_exit(&msh, ERR_MALLOC);
	execute_cmd(msh);
	restore_redirection(msh);
	free_double_str(&msh->exec.exec_arg);
}

//main function for execution line or pipe
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
