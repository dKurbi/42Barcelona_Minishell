/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:53:11 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/09 19:18:27 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//ejecutar los comandos ejemplo: "ls -la"
void	execution_cmd(t_msh *msh, int mode)
{
	if (mode == EXECUTE_COMMAND)
	{
		msh->exec.exec_arg = get_exec_argv(msh, msh->lst_line);
		if (!msh->exec.exec_arg)
			print_error_exit(&msh, ERR_MALLOC);
		control_redirection(msh);
		restore_redirection(msh);
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
		execution_cmd(msh, EXECUTE_PIPE);
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
		execution_cmd(msh, EXECUTE_COMMAND);
}
