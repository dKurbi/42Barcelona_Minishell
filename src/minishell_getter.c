/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_getter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:56:35 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/10 20:45:10 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/* 
char	*get_raw_cmd(t_msh *msh)
{
	
}
*/

void	get_cmd_with_path(t_msh **msh)
{
	char	**split;
	int		i;
	char	*s;

	split = ft_split((*msh)->exec.path, ':');
	if (!split)
		return ;
	//px_find_cmd_loop(info, &split, -1);

	i = -1;
	s = NULL;
	while (split[++i])
	{
		s = ft_strdup(split[i]);
		if (!s)
		{
			ft_split_free(split);
			return ;
		}
		free_str(&split[i]);
		split[i] = ft_strjoin(s, "/");
		(*msh)->exec.cmd_with_path = ft_strjoin(split[i], (*msh)->exec.exec_arg[0]);
		if (access((*msh)->exec.cmd_with_path, X_OK) == 0)
		{
			free_str(&s);
			break ;
		}
		free_str(&(*msh)->exec.cmd_with_path);
		free_str(&s);
	}
	free_double_str(&split);
}


char	*get_path(t_msh *msh)
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

//( execve(..., char *const argv[], ...); )
//ATENCION: esto nos servira solo para los t_line,
//porque tenemos que crear cada vez este argv** en 
char	**get_exec_argv(t_msh *msh, t_line *lst_line)
{
	char	**exe_arg;
	t_line	*copy_lst;
	int		i;

	if (lst_line == NULL)
		return (NULL);
	exe_arg = (char **) malloc(sizeof(char *) * \
			(calculate_len_lst_line(lst_line) + 1));
	if (!exe_arg)
		print_error_exit(&msh, ERR_MALLOC);
	copy_lst = lst_line;
	i = 0;
	while (copy_lst != NULL)
	{
		if (!is_redirection(copy_lst->type))
		{
			exe_arg[i] = ft_strdup(copy_lst->str);
			if (exe_arg[i++] == NULL)
				return (ft_split_free(exe_arg));
		}
		else
			copy_lst = copy_lst->next;
		if (copy_lst)
			copy_lst = copy_lst->next;
	}
	exe_arg[i] = NULL;
	return (exe_arg);
}
