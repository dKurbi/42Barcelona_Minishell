/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:04:41 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/06 10:21:47 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	increment_shlvl(char ***r)
{
	char	**rtn;
	int		i;
	char	*new_level;

	i = 0;
	rtn = *r;
	while (ft_strncmp(rtn[i], "SHLVL=", 6))
		i++;
	new_level = ft_itoa(ft_atoi(rtn[i] + 6) + 1);
	if (!new_level)
	{
		free_double_str(r);
		return ;
	}
	free_str(&rtn[i]);
	rtn[i] = ft_strjoin("SHLVL=", new_level);
	if (!rtn[i])
	{
		free_double_str(r);
		free_str(&new_level);
		return ;
	}
	free_str(&new_level);
}

char	**create_env(char **env)
{
	int		n_lines;
	char	**rtn;

	n_lines = 0;
	while (env[n_lines])
		n_lines++;
	rtn = (char **) malloc(sizeof(char *) * (n_lines + 1));
	if (rtn)
	{
		n_lines = -1;
		while (env[++n_lines])
		{
			rtn[n_lines] = ft_strdup(env[n_lines]);
			if (!rtn[n_lines])
				return (ft_split_free(rtn));
		}
		rtn[n_lines] = NULL;
		increment_shlvl(&rtn);
	}
	return (rtn);
}

void	builtin_env_print_all(t_msh *msh)
{
	int	i;

	i = -1;
	while (msh->ev[++i])
	{
		if (!(msh->ev[i][0] >= 'a' && msh->ev[i][0] <= 'z'))
			printf("%s\n", msh->ev[i]);
	}
}

int	builtin_env(t_msh *msh)
{
	if (!msh->exec.exec_arg[1])
		builtin_env_print_all(msh);
	else
	{
		print_warning_with_arg("env", ERR_BUILTIN_HAS_ARGS);
		return (1);
	}
	return (0);
}
