/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:07:35 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/09 15:54:40 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

int	execute_child_argv(t_msh **msh)
{
	char	*tmp;

	if (!(*msh)->exec.exec_arg)
		print_error_exit(msh, ERR_MALLOC);
	if (!(*msh)->exec.exec_arg[0])
		return (1);
	if ((*msh)->exec.exec_arg[0][0] == QUOTE || \
		(*msh)->exec.exec_arg[0][0] == DQUOTE)
	{
		if ((*msh)->exec.exec_arg[0][0] == QUOTE)
			tmp = ft_strtrim((*msh)->exec.exec_arg[0], "\'");
		else
			tmp = ft_strtrim((*msh)->exec.exec_arg[0], "\"");
		free((*msh)->exec.exec_arg[0]);
		(*msh)->exec.exec_arg[0] = tmp;
	}
	return (0);
}

void	execute_check_command(t_msh *msh)
{
	int	command_status;

	command_status = 127;
	get_cmd_with_path(&msh);
	if (check_command(msh->exec.cmd_with_path) == 1)
	{
		if (access(msh->exec.exec_arg[0], F_OK) < 0 \
				&& msh->exec.exec_arg[0][0] != '/')
			print_warning_with_arg(msh->exec.exec_arg[0], ERR_NO_CMD);
		else if (access(msh->exec.exec_arg[0], F_OK) < 0)
			print_warning_with_arg(msh->exec.exec_arg[0], ERR_FILE_NO_EXIST);
		else
		{
			command_status = 126;
			print_warning_with_arg(msh->exec.exec_arg[0], ERR_NO_PERM);
		}
		exit_free_child(msh, command_status);
	}
}

void	execute_check_command_and_execve(t_msh *msh)
{
	if (!msh->exec.exec_arg[0])
		exit_free_child(msh, 0);
	msh->exec.dir = opendir(msh->exec.exec_arg[0]);
	if (msh->exec.dir)
	{
		print_warning_with_arg(msh->exec.exec_arg[0], ERR_IS_DIR);
		exit_free_child(msh, 126);
	}
	if (check_command(msh->exec.exec_arg[0]) == 1)
		execute_check_command(msh);
	if (msh->exec.cmd_with_path == NULL)
	{
		if (if_script(msh, msh->exec.exec_arg[0]))
			change_exec_arg_script(msh);
		execve(msh->exec.exec_arg[0], msh->exec.exec_arg, msh->ev);
	}
	else
		execve(msh->exec.cmd_with_path, msh->exec.exec_arg, msh->ev);
}

void	execute_child(t_msh *msh)
{
	if (control_redirection(msh))
	{
		ft_close(&msh->exec.fd_stdin);
		ft_close(&msh->exec.fd_stdout);
		ft_close(&msh->exec.pip[0]);
		ft_close(&msh->exec.pip[1]);
		g_exit_status = 1;
		exit(g_exit_status);
	}
	signal_control_exec(msh);
	if (execute_child_argv(&msh))
		exit_free_child(msh, 0);
	msh->exec.path = search_path(msh);
	execute_check_command_and_execve(msh);
	exit_free_child(msh, g_exit_status);
}

//execute command WITHOUT pipes
void	execute_cmd(t_msh *msh)
{
	signal_control_block();
	if (msh->exec.exec_arg[0] && check_ifbuiltin(msh->exec.exec_arg[0]))
	{
		execute_builtin(msh);
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
			ft_close(&msh->exec.fd_here_doc[0]);
	}
	ft_close(&msh->exec.pip[0]);
	ft_close(&msh->exec.pip[1]);
	wait_process(msh, msh->exec.proc, ONE_COMMAND);
	g_exit_status = msh->exit_status;
}
