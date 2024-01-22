/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_unset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:05:05 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/22 15:02:09 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void unset_env_line(t_msh *msh, int line_num)
{
	char 	**new_env;
	int		i;
	int 	j;
	
	new_env = malloc(env_len(msh) * sizeof(char *));
	if (!new_env)
		print_error_exit(&msh, ERR_MALLOC);
	i = -1;
	j = -1;
	while(msh->ev[++i])
	{
		if (i != line_num)
			new_env[++j] = ft_strdup(msh->ev[i]);
	}
	new_env[++j] = NULL;
	free_double_str(&msh->ev);
	msh->ev = new_env;	
}
int	builtin_unset(t_msh *msh)
{
	char	*var;
	int		i;
	int		line_num;
	
	i = 0;
	while (msh->exec.exec_arg[++i])
	{
		var = ft_strdup(msh->exec.exec_arg[i]);
		if (!var)
			print_error_exit(&msh, ERR_MALLOC);
		line_num = lineof_var_in_env(msh, var);
		if (line_num != -1)
			unset_env_line(msh, line_num);
	}
	return (0);
}
