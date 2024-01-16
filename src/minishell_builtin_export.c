/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:03:50 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/16 13:47:35 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_export_print_all(t_msh *msh)
{
	int	i;

	i = -1;
	while (msh->ev[++i])
	{
		
	}
}

int	builtin_export(t_msh *msh)
{
	if (!msh->exec.exec_arg[1])
		builtin_export_print_all(msh);
	return (0);
}
