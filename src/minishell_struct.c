/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:07:57 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/16 18:53:15 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_msh	*mshnew(char **env)
{
	t_msh	*msh;

	msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		return (NULL);
	msh->ev = env;
	msh->lst_line = NULL;
	msh->read_line = NULL;
	msh->pipe_active = 0;
	msh->parser = parsernew();
	msh->exec = execnew();
	return (msh);
}

t_parser	parsernew(void)
{
	t_parser	parser;

	parser.cmd = NULL;
	parser.path = NULL;
	parser.split_path = NULL;
	parser.raw_cmd = NULL;
	return (parser);
}

t_exec	execnew(void)
{
	t_exec	exec;

	exec.cmd = NULL;
	exec.exe_arg = NULL;
	exec.path = NULL;
	exec.proc = 0;
	exec.raw_cmd = NULL;
	exec.split_path = NULL;
	exec.wait_status = 0;
	return (exec);
}
