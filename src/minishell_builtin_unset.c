/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_unset.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:05:05 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/24 19:12:53 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset_env_line(t_msh *msh, int line_num)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **) malloc(sizeof(char *) * env_len(msh));
	if (!new_env)
		print_error_exit(&msh, ERR_MALLOC);
	i = -1;
	j = -1;
	while (msh->ev[++i])
	{
		if (i != line_num)
			new_env[++j] = ft_strdup(msh->ev[i]);
	}
	new_env[++j] = NULL;
	free_double_str(&msh->ev);
	msh->ev = new_env;
}

int	unset_check_var(char **exec_arg)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (exec_arg[i])
	{
		if (check_ifempty_str(exec_arg[i]) || \
			ft_strchr(exec_arg[i], '=') || ft_isdigit(exec_arg[i][0]))
		{
			print_warning_with_3_arg("unset", exec_arg[i], ERR_INVALID_INDENT);
			status = 1;
		}
		i++;
	}
	return (status);
}

int	builtin_unset(t_msh *msh)
{
	char	*var;
	int		i;
	int		line_num;

	if (unset_check_var(msh->exec.exec_arg))
	{
		return (1);
	}
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
