/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:04:41 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/22 14:23:35 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//*var is malloced!!!
int	if_var_in_env(t_msh *msh, char *var)
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
			return (1);
		}
	}
	free_str(&var);
	return (0);
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

char	**create_env(char **env)
{
	int		n_lines;
	char	**rtn;

	n_lines = 0;
	while (env[n_lines])
		n_lines++;
	rtn = (char **) malloc(sizeof(char *) * (n_lines + 1));
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

int	env_len(t_msh *msh)
{
	int	i;

	i = 0;
	while(msh->ev[i])
		i++;
	return (i);
}
