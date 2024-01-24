/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_env_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:04:10 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/24 20:15:39 by iassambe         ###   ########.fr       */
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

int	if_var_in_env_no_eq(t_msh *msh, char *var, int len)
{
	int		i;
	char	*join_var_eq;

	join_var_eq = ft_strjoin(var, "=");
	if (!join_var_eq)
		print_error_exit(&msh, ERR_MALLOC);
	i = 0;
	while (msh->ev[i])
	{
		if (ft_strncmp(msh->ev[i], join_var_eq, len + 1) == 0 || \
			(ft_strncmp(msh->ev[i], var, len) == 0 && msh->ev[i][len] == '\0'))
		{
			free_str(&join_var_eq);
			free_str(&var);
			return (i);
		}
		i++;
	}
	free_str(&join_var_eq);
	free_str(&var);
	return (-1);
}

//*var is malloced!!!
// return -1 (NEGATIVE) if NOT IN **ev, 0 or POSITIVE (> 0) if IN **ev
int	if_var_in_env(t_msh *msh, char *var)
{
	int	i;
	int	len;

	len = len_before_equal(var);
	if (!ft_strrchr(var, '='))
		return (if_var_in_env_no_eq(msh, var, len));
	i = 0;
	while (msh->ev[i])
	{
		if (ft_strncmp(msh->ev[i], var, len) == 0 || \
	(ft_strncmp(msh->ev[i], var, len - 1) == 0 && msh->ev[i][len] == '\0'))
		{
			free_str(&var);
			return (i);
		}
		i++;
	}
	free_str(&var);
	return (-1);
}
