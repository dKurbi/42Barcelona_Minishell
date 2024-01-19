/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:52:29 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/15 20:33:36 by iassambe         ###   ########.fr       */
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
			return (home + 5);
		}
	}
	return (home);
}

char	*builtin_cd_join_home(t_msh *msh)
{
	char	*join;

	if (!msh->exec.exec_arg[1])
		return (ft_strdup(search_home(msh)));
	join = ft_strjoin(search_home(msh), msh->exec.exec_arg[1] + 1);
	return (join);
}

void	builtin_cd_change_pwds(t_msh *msh, char ***ev)
{
	char	*current_dir;
	int		i;
	char	*search_pwd_old;

	i = -1;
	current_dir = NULL;
	search_pwd_old = ft_strdup(search_pwd(msh));
	while ((*ev)[++i])
	{
		if (ft_strnstr((*ev)[i], "OLDPWD=", 7) != NULL)
		{
			free_str(&(*ev)[i]);
			(*ev)[i] = ft_strjoin("OLDPWD=", search_pwd_old);
			free(search_pwd_old);
		}
		if (ft_strnstr((*ev)[i], "PWD=", 4) != NULL)
		{
			free_str(&(*ev)[i]);
			current_dir = getcwd(NULL, 0);
			(*ev)[i] = ft_strjoin("PWD=", current_dir);
			free(current_dir);
		}
		if (!(*ev)[i])
			print_error_exit(&msh, ERR_MALLOC);
	}
}

int	builtin_cd_change_dir(t_msh *msh, char *str)
{
	(void)(msh);
	if (!str || chdir(str) < 0)
	{
		print_perror_with_arg("cd", str);
		free_str(&str);
		return (1);
	}
	free_str(&str);
	builtin_cd_change_pwds(msh, &msh->ev);
	return (0);
}

int	builtin_cd(t_msh *msh)
{
	int	cd_exit_status;

	cd_exit_status = 0;
	if (!msh->exec.exec_arg[1] || (msh->exec.exec_arg[1][0] == '~' && \
		(msh->exec.exec_arg[1][1] == '\0' || msh->exec.exec_arg[1][1] == '/')))
		cd_exit_status = builtin_cd_change_dir(msh, builtin_cd_join_home(msh));
	else if (!ft_strncmp(msh->exec.exec_arg[1], "-", 1) && \
			ft_strlen(msh->exec.exec_arg[1]) == 1)
		cd_exit_status = builtin_cd_change_dir(msh, \
		ft_strdup(search_oldpwd(msh)));
	else
		cd_exit_status = builtin_cd_change_dir(msh, \
		ft_strdup(msh->exec.exec_arg[1]));
	return (cd_exit_status);
}
