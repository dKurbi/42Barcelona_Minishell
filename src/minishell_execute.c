/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:53:11 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/11 20:31:38 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_cmd(t_msh *msh)
{
	char	*tmp;

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
		return ;
	if (check_command(msh->exec.exec_arg[0]) == 1)
	{
		get_cmd_with_path(&msh);
		if (check_command(msh->exec.cmd_with_path) == 1)
		{
			print_warning_with_arg(msh->exec.exec_arg[0], ERR_NO_CMD);
			return ;
		}
	}
	if (msh->exec.cmd_with_path == NULL)
		execve(msh->exec.exec_arg[0], msh->exec.exec_arg, msh->ev);
	else
		execve(msh->exec.cmd_with_path, msh->exec.exec_arg, msh->ev);
}

//ejecutar los comandos ejemplo: "ls -la"
void	execution_line(t_msh *msh, int mode)
{
	if (mode == EXECUTE_COMMAND)
	{
		msh->exec.exec_arg = get_exec_argv(msh, msh->lst_line);
		if (!msh->exec.exec_arg)
			print_error_exit(&msh, ERR_MALLOC);
		printf("control_redirection\n\n");
		control_redirection(msh);
		printf("execute_cmd\n\n");
		execute_cmd(msh);
		printf("restore_redirection\n\n");
		restore_redirection(msh);
		printf("free_double_str exec_line\n\n");
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
	(void)(msh);
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
