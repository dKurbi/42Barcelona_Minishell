/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_cd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:52:29 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/10 20:08:52 by iassambe         ###   ########.fr       */
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

	i = -1;
	current_dir = NULL;
	change_old_pwd(msh, ev);
	while ((*ev)[++i])
	{
		if (ft_strnstr((*ev)[i], "PWD=", 4) != NULL)
		{
			free_str(&(*ev)[i]);
			current_dir = getcwd(NULL, 0);
			(*ev)[i] = ft_strjoin("PWD=", current_dir);
			if (!(*ev)[i])
				print_error_exit(&msh, ERR_MALLOC);
			free(current_dir);
		}
	}
}

int	builtin_cd_change_dir(t_msh *msh, char *str)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!str || chdir(str) < 0)
	{
		if (!search_oldpwd(msh))
			print_warning_with_arg("cd", ERR_NO_OLDPWD);
		else
			print_perror_with_arg("cd", str);
		free_2_str(&str, &current_dir);
		return (1);
	}
	if (!current_dir && !ft_strncmp(str, ".", 1) && ft_strlen(str) == 1)
		ft_putstr_fd(ERR_NO_CURR_DIR, 2);
	else
		builtin_cd_change_pwds(msh, &msh->ev);
	free_2_str(&str, &current_dir);
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
