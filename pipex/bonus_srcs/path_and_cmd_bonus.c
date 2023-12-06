/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_cmd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:08:01 by iassambe          #+#    #+#             */
/*   Updated: 2023/10/19 20:19:23 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_inc/pipex_bonus.h"

/*
find the full path of system;
example: /usr/bin:/usr/sbin:/usr/local/sbin;
*/
char	*px_find_path(t_info **info)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while ((*info)->ev[++i])
	{
		if (ft_strnstr((*info)->ev[i], "PATH=", 6) != NULL)
		{
			path = (*info)->ev[i];
			return (path + 5);
		}
	}
	return (path);
}

/*
checks if av[i] is already a valid cmd;
ex.: ./pipex infile /usr/bin/cat "/usr/local/bin/norminette" outfile;
*/
int	px_if_av_cmd_x_ok(t_info **info, int i)
{
	char	*cmd2;

	if (access((*info)->av[i], X_OK) == 0)
	{
		(*info)->cmd = ft_strdup((*info)->av[i]);
		return (1);
	}
	cmd2 = px_cut_bef_space((*info)->av[i]);
	if (access(cmd2, X_OK) == 0)
	{
		(*info)->cmd = ft_strdup(cmd2);
		free(cmd2);
		return (1);
	}
	free(cmd2);
	return (0);
}

//loop for px_find_cmd() to find info->cmd;
void	px_find_cmd_loop(t_info **info, char ***split, int i)
{
	char	*s;

	s = NULL;
	while ((*split)[++i])
	{
		s = ft_strdup((*split)[i]);
		if (!s)
			return ;
		px_free_string(&(*split)[i]);
		(*split)[i] = ft_strjoin(s, "/");
		(*info)->cmd = ft_strjoin((*split)[i], (*info)->raw_cmd);
		if (access((*info)->cmd, X_OK) == 0)
		{
			px_free_string(&s);
			break ;
		}
		px_free_string(&(*info)->cmd);
		px_free_string(&s);
	}
}

/*
find full command with PATH for executin execve();
(example: /usr/bin/ld, /usr/bin/cc);
i - number in info->av;
*/
void	px_find_cmd(t_info **info, int i)
{
	char	*path;
	char	**split;

	if (px_if_av_cmd_x_ok(info, i) == 1)
		return ;
	path = px_find_path(info);
	if (!path || px_check_ifempty(path))
	{
		px_print_error((*info), 3, -1);
		infofree(info, 0);
		exit(127);
	}
	split = ft_split(path, ':');
	if (!split)
		return ;
	(*info)->raw_cmd = px_cut_bef_space((*info)->av[i]);
	if (!(*info)->raw_cmd)
	{
		px_free_split(&split);
		return ;
	}
	px_find_cmd_loop(info, &split, -1);
	px_free_split(&split);
}
