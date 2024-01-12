/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:53:11 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/12 20:26:05 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

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
