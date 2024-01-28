/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:53:11 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/28 16:29:53 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

void	execute_builtin(t_msh *msh)
{
	msh->exec.exec_arg = get_exec_argv(msh, msh->lst_line);
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

//ejecutar los comandos ejemplo: "ls -la"
void	execution_line(t_msh *msh, int mode)
{
	signal_control_block(msh);
	if (mode == EXECUTE_COMMAND)
	{
		g_exit_status = check_heredoc(msh);
		if (g_exit_status > 0)
			return ;
		execute_cmd(msh);
		restore_redirection(msh);
		free_double_str(&msh->exec.exec_arg);
	}
	else if (mode == EXECUTE_PIPE)
	{
		execute_cmd_pipe(msh);
		
	}
}

//ejecutar los comandos ejemplo: "ls -la | wc -l"
void	execution_pipes(t_msh *msh)
{
	t_pipe	*copy_pipe;

	copy_pipe = msh->lst_pipe;
	while (copy_pipe)
	{
		execution_line(msh, EXECUTE_PIPE);//no esta HECHO
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
