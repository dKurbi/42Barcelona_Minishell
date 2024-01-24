/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_env_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:04:10 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/24 17:40:53 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	env_len(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->ev[i])
		i++;
	return (i);
}

int	lineof_var_in_env(t_msh *msh, char *var)
{
	int	i;
	int	len;

	len = len_before_equal(var);
	i = -1;
	while (msh->ev[++i])
	{
		if (ft_strncmp(msh->ev[i], var, len) == 0)
		{
			free_str(&var);
			return (i);
		}
	}
	free_str(&var);
	return (-1);
}
