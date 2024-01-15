/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:52:29 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/15 03:25:57 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*search_home(t_msh *msh)
{
	char	*home;
	int		i;

	i = -1;
	home = NULL;
	while (msh->ev[++i])
	{
		if (ft_strnstr(msh->ev[i], "HOME=", 5) != NULL)
		{
			home = msh->ev[i];
			return (ft_strdup(home + 5));
		}
	}
	return (home);
}

int	builtin_cd_change_dir(t_msh *msh, char *str)
{
	(void)(msh);
	if (!str || chdir(str) < 0)
	{
		print_warning_with_arg("cd", ERR_FILE_NO_EXIST);
		free_str(&str);
		return (1);
	}
	free_str(&str);
	return (0);
}

int	builtin_cd(t_msh *msh)
{
	if (!msh->exec.exec_arg[1] || (!ft_strncmp(msh->exec.exec_arg[1], "~", 1) \
		&& ft_strlen(msh->exec.exec_arg[1]) == 1))
		builtin_cd_change_dir(msh, search_home(msh));
	else if (msh->exec.exec_arg[2])
	{
		print_warning_with_arg("cd", ERR_BUILTIN_HAS_ARGS);
		return (2);
	}
	else
		builtin_cd_change_dir(msh, ft_strdup(msh->exec.exec_arg[1]));
	return (0);
}