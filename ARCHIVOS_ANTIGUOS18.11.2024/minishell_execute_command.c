/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:07:35 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/16 16:37:41 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

int	execute_child_argv(t_msh **msh)
{
	char	*tmp;

	(*msh)->exec.exec_arg = get_exec_argv((*msh), (*msh)->lst_line);
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
	if (check_command(msh->exec.exec_arg[0]) == 1)
	{
		get_cmd_with_path(&msh);
		if (check_command(msh->exec.cmd_with_path) == 1)
		{
			print_warning_with_arg(msh->exec.exec_arg[0], ERR_NO_CMD);
			exit_free_child(msh, 127);
		}
	}
}

void	execute_execve(t_msh *msh)
{
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
	if (execute_child_argv(&msh))
		exit_free_child(msh, 1);
	msh->exec.path = search_path(msh);
	if (!msh->exec.path)
		exit_free_child(msh, 127);
	execute_check_command(msh);
	execute_execve(msh);
	exit_free_child(msh, g_exit_status);
}

void	execute_cmd(t_msh *msh)
{
	signal_control_exec(msh);
	if (check_ifbuiltin(msh->lst_line->str))
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
		execute_child(msh);
	close(msh->exec.pip[0]);
	close(msh->exec.pip[1]);
	waitpid(msh->exec.proc, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
	{
		g_exit_status = WEXITSTATUS(g_exit_status);
		if (g_exit_status == 3)
			g_exit_status = 131;
	}
}
