/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_getter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:56:35 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/12 17:03:30 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_cmd_with_path(t_msh **msh)
{
	char	**split;
	int		i;
	char	*s;

	split = ft_split((*msh)->exec.path, ':');
	if (!split)
		return ;
	i = -1;
	while (split[++i])
	{
		s = ft_strdup(split[i]);
		if (!s)
		{
			ft_split_free(split);
			return ;
		}
		free_str(&split[i]);
		split[i] = get_ft_strjoin_modif(s, "/");
		(*msh)->exec.cmd_with_path = ft_strjoin(split[i], \
									(*msh)->exec.exec_arg[0]);
		if (access((*msh)->exec.cmd_with_path, X_OK) == 0)
			break ;
		free_str(&(*msh)->exec.cmd_with_path);
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

//2 - no es redir, 1 - malloc err, 0 - es redir
int	get_exec_argv_loop(t_line *copy_lst, char ***exe_arg, int *i)
{
	while (copy_lst != NULL)
	{
		if (!is_redirection(copy_lst->type))
		{
			(*exe_arg)[*i] = ft_strdup(copy_lst->str);
			if ((*exe_arg)[(*i)++] == NULL)
				return (1);
		}
		else
			copy_lst = copy_lst->next;
		if (copy_lst)
			copy_lst = copy_lst->next;
	}
	return (0);
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
	if (get_exec_argv_loop(copy_lst, &exe_arg, &i) == 1)
		return (ft_split_free(exe_arg));
	exe_arg[i] = NULL;
	return (exe_arg);
}

char	*get_shell(t_msh *msh)
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

void change_exe_arg_script(t_msh *msh)
{
	char **str;
	int	i;

	i = 0;
	while (msh->exec.exec_arg[i])	
		i++;
	str = malloc(sizeof(char *) * (i + 2));
	if (str == NULL)
		print_error_exit(&msh, ERR_MALLOC);
	str[0] = ft_strdup(get_shell(msh));
	i = -1;
	while(msh->exec.exec_arg[++i])
		str[i + 1] = ft_strdup(msh->exec.exec_arg[i]);
	str[i + 1] = NULL;
	free_double_str(&msh->exec.exec_arg);
	msh->exec.exec_arg = str;
}