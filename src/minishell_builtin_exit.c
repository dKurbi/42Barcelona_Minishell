/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:05:26 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/16 13:29:37 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_exit(t_msh *msh)
{
	if (msh->exec.exec_arg[1])
	{
		
	}
	return (0);
}
