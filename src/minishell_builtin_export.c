/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:03:50 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/16 17:36:45 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_export_print_all(t_msh *msh)
{
	int	i;
	int	j;

	i = -1;
	while (msh->ev[++i])
	{
		j = -1;
		printf("declare -x ");
		while (msh->ev[i][++j] && msh->ev[i][j] != '=')
			printf("%c", msh->ev[i][j]);
		if (msh->ev[i][j])//no esta testeado, esto es el caso si anadimos sin = ( ejemplo: delcare -x variable )
		{
			printf("%c", msh->ev[i][j++]);
			printf("%c", DQUOTE);
			while (msh->ev[i][j])
				printf("%c", msh->ev[i][j++]);
			printf("%c", DQUOTE);
		}
		printf("\n");
	}
}

void	export_change_var(char **ev)
{
	
}

char	**append_to_env(char **old_env)
{
	char	**new_env;

	
}

void	builtin_export_add_all(t_msh *msh)
{
	int	i;

	i = 0;
	while (msh->exec.exec_arg[++i])
	{
		//code
	}
}

int	builtin_export(t_msh *msh)
{
	if (!msh->exec.exec_arg[1])
		builtin_export_print_all(msh);
	else
		builtin_export_add_all(msh);
	return (0);
}
