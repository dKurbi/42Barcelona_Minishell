/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:53:11 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/12 14:46:26 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

void execute_child(t_msh *msh, char *tmp)
{
	msh->exec.exec_arg = get_exec_argv(msh, msh->lst_line);
	if (!msh->exec.exec_arg)
		print_error_exit(&msh, ERR_MALLOC);
	if (!msh->exec.exec_arg[0])
		exit(1);
	if (msh->exec.exec_arg[0][0] == QUOTE || msh->exec.exec_arg[0][0] == QUOTE)
	{
		if (msh->exec.exec_arg[0][0] == QUOTE)
			tmp = ft_strtrim(msh->exec.exec_arg[0], "\'");
		else
			tmp = ft_strtrim(msh->exec.exec_arg[0], "\"");
		free(msh->exec.exec_arg[0]);
		msh->exec.exec_arg[0] = tmp;
	}
	msh->exec.path = get_path(msh);
	if (!msh->exec.path)
		exit(127);
	if (check_command(msh->exec.exec_arg[0]) == 1)
	{
		get_cmd_with_path(&msh);
		if (check_command(msh->exec.cmd_with_path) == 1)
		{
			print_warning_with_arg(msh->exec.exec_arg[0], ERR_NO_CMD);
			exit(127);
		}
	}
	if (msh->exec.cmd_with_path == NULL)
		execve(msh->exec.exec_arg[0], msh->exec.exec_arg, msh->ev);
	else
		execve(msh->exec.cmd_with_path, msh->exec.exec_arg, msh->ev);
	exit(g_exit_status);
}

void	execute_cmd(t_msh *msh)
{
	char	*tmp;

	tmp = NULL;
	//signal_control_exec(msh);
	if (pipe(msh->exec.pip) < 0)
		print_error_exit(&msh, ERR_PIPE);
	msh->exec.proc = fork();
	if (msh->exec.proc < 0)
		print_error_exit(&msh, ERR_FORK);
	if (msh->exec.proc == 0)
		execute_child(msh, tmp);
	close(msh->exec.pip[0]);
	close(msh->exec.pip[1]);
	waitpid(msh->exec.proc, &g_exit_status, 0);
	/////
	g_exit_status = WEXITSTATUS(g_exit_status);
}

//ejecutar los comandos ejemplo: "ls -la"
void	execution_line(t_msh *msh, int mode)
{
	if (mode == EXECUTE_COMMAND)
	{
		control_redirection(msh);
		execute_cmd(msh);
		restore_redirection(msh);
		free_double_str(&msh->exec.exec_arg);
	}
	else if (mode == EXECUTE_PIPE)
	{
		//msh->exec.exec_arg = get_exec_argv(msh, msh->lst_pipe->lst_line);
		//hacer despues
	}
}

//ejecutar los comandos ejemplo: "ls -la | wc -l"
void	execution_pipes(t_msh *msh)
{
	while (msh->lst_line)
	{
		execution_line(msh, EXECUTE_PIPE);
	}
}

//luego para executing
void	execution(t_msh *msh)
{
	if (check_ifempty_str(msh->read_line) && msh->read_line[0] != '\0')
		return ;
	if (msh->lst_pipe != NULL)
		execution_pipes(msh);
	else
		execution_line(msh, EXECUTE_COMMAND);
}
