/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:07:57 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/12 16:12:17 by dkurcbar         ###   ########.fr       */
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
	msh->exec.cmd = NULL;
	msh->exec.exe_arg = NULL;
	msh->exec.path = NULL;
	msh->exec.proc = 0;
	msh->exec.raw_cmd = NULL;
	msh->exec.split_path = NULL;
	msh->exec.wait_status = 0;
	msh->line = NULL;
	return (msh);
}