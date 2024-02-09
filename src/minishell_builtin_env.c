/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:04:41 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/09 03:31:04 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	increment_shlvl(t_msh *msh, char ***r, char *if_shlvl)
{
	char	**rtn;
	int		i;
	char	*new_level;

	i = 0;
	rtn = *r;
	while (rtn[i] && ft_strncmp(rtn[i], "SHLVL=", 6))
		i++;
	if (!if_shlvl)
		return ;
	new_level = ft_itoa(ft_atoi(rtn[i] + 6) + 1);
	if (!new_level)
		print_error_exit(&msh, ERR_MALLOC);
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

void	create_env_fill(t_msh *msh, char **old_ev, char ***ev, char *if_shlvl)
{
	int	n_lines;

	n_lines = -1;
	while (old_ev[++n_lines])
	{
		(*ev)[n_lines] = ft_strdup(old_ev[n_lines]);
		if (!(*ev)[n_lines])
		{
			ft_split_free((*ev));
			return ;
		}
	}
	if (!if_shlvl)
		(*ev)[n_lines++] = ft_strdup("SHLVL=0");
	(*ev)[n_lines] = NULL;
	increment_shlvl(msh, ev, if_shlvl);
}

char	**create_env(t_msh *msh, char **env)
{
	int		n_lines;
	char	**rtn;

	if (*env)
	{
		n_lines = 0;
		while (env[n_lines])
			n_lines++;
		if (!search_shlvl(env))
			n_lines++;
		rtn = (char **) malloc(sizeof(char *) * (n_lines + 1));
		if (rtn)
			create_env_fill(msh, env, &rtn, search_shlvl(env));
		return (rtn);
	}
	else
		return (env_empty());
}

void	builtin_env_print_all(t_msh *msh)
{
	int	i;

	i = -1;
	while (msh->ev[++i])
	{
		printf("%s\n", msh->ev[i]);
	}
}

//env: show environment
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
