/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:04:41 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/15 02:55:17 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**create_env(char **env)
{
	int		n_lines;
	char	**rtn;

	n_lines = 0;
	while (env[n_lines])
		n_lines++;
	rtn = (char **)malloc(sizeof(char *) * (n_lines + 1));
	n_lines = -1;
	while (env[++n_lines])
	{
		rtn[n_lines] = ft_strdup(env[n_lines]);
		if (!rtn[n_lines])
			return (ft_split_free(rtn));
	}
	rtn[n_lines] = NULL;
	return (rtn);
}

int	builtin_env(t_msh *msh)
{
	(void)(msh);
	return (0);
}