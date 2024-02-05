/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:07:35 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/05 19:16:48 by iassambe         ###   ########.fr       */
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

void	execute_check_command_and_execve(t_msh *msh)
{
	msh->exec.dir = opendir(msh->exec.exec_arg[0]);
	if (msh->exec.dir)
	{
		closedir(msh->exec.dir);
		print_warning_with_arg(msh->exec.exec_arg[0], ERR_IS_DIR);
		exit_free_child(msh, 126);
	}
	if (check_command(msh->exec.exec_arg[0]) == 1)
	{
		get_cmd_with_path(&msh);
		if (check_command(msh->exec.cmd_with_path) == 1)
		{
			print_warning_with_arg(msh->exec.exec_arg[0], ERR_NO_CMD);
			exit_free_child(msh, 127);
		}
	}
	if (msh->exec.cmd_with_path == NULL)
	{
		if (if_srcipt(msh->exec.exec_arg[0]))
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
		exit_free_child(msh, 1);
	msh->exec.path = search_path(msh);
	if (!msh->exec.path)
		exit_free_child(msh, 127);
	execute_check_command_and_execve(msh);
	exit_free_child(msh, g_exit_status);
}

void	execute_cmd(t_msh *msh)
{
	signal_control_block(msh);
	if (msh->exec.exec_arg[0] && check_ifbuiltin(msh->exec.exec_arg[0]))
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
			ft_close(&msh->exec.fd_here_doc[0]);
	}
	ft_close(&msh->exec.pip[0]);
	ft_close(&msh->exec.pip[1]);
	wait_process(msh, msh->exec.proc, ONE_COMMAND);
	g_exit_status = msh->exit_status;
}

//waiting to all commands and return it's status
void	wait_process(t_msh *msh, pid_t pid, int num_commands)
{
	int	status;

	while (num_commands >= 0)
	{
		num_commands--;
		if (pid == wait(&status))
		{
			if (WIFEXITED(status))
				msh->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					msh->exit_status = 130;
					printf("\n");
				}
				else if (WTERMSIG(status) == SIGQUIT)
				{
					msh->exit_status = 131;
					printf("\nQuit: 3\n");
				}
			}
		}
	}
}
void	waitpid_process(t_msh *msh, pid_t pid, int num_commands)
{
	int	status;

	(void) pid;
	while (num_commands >= 0)
	{
		num_commands--;
		waitpid(-1, &status, 0);
			if (WIFEXITED(status))
				msh->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					msh->exit_status = 130;
					printf("\n");
				}
				else if (WTERMSIG(status) == SIGQUIT)
				{
					msh->exit_status = 131;
					printf("\nQuit: 3\n");
				}
			}
		//}
	}
}
