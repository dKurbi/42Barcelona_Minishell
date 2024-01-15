/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:45:50 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/14 23:48:02 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*search_path(t_msh *msh)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (msh->ev[++i])
	{
		if (ft_strnstr(msh->ev[i], "PATH=", 5) != NULL)
		{
			path = msh->ev[i];
			return (ft_strdup(path + 5));
		}
	}
	return (path);
}

char	*search_shell(t_msh *msh)
{
	char	*shell_str;
	int		i;

	i = -1;
	shell_str = NULL;
	while (msh->ev[++i])
	{
		if (ft_strnstr(msh->ev[i], "SHELL=", 6) != NULL)
		{
			shell_str = msh->ev[i];
			return (shell_str + 6);
		}
	}
	return (shell_str);
}

char	*search_pwd(t_msh *msh)
{
	char	*pwd;
	int		i;

	i = -1;
	pwd = NULL;
	while (msh->ev[++i])
	{
		if (ft_strnstr(msh->ev[i], "PWD=", 4) != NULL)
		{
			pwd = msh->ev[i];
			return (pwd + 4);
		}
	}
	return (pwd);
}