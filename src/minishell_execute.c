/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:53:11 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/06 18:33:59 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execution_cmd(t_msh *msh, int mode) //ejecutar los comandos ejemplo: "ls -la"
{
	(void)(msh);
	(void)(mode);
}

void	execution_pipes(t_msh *msh) //ejecutar los comandos ejemplo: "ls -la | wc -l"
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
