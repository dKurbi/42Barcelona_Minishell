/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_getter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:56:35 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/12 16:56:23 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//str with '
char	*get_str_quotes(int quotes)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *) malloc(sizeof(char) * (quotes + 1));
	if (!s)
		return (NULL);
	while (i < quotes)
	{
		s[i] = QUOTE;
		i++;
	}
	s[i] = '\0';
	return (s);
}

//save in msh->exec.cmd_with_path command with $PATH (example: /bin/ls)
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
			break ;
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

//2 - is not redirection, 1 - malloc err, 0 - is redirection
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

//get the array for executing from lst_line
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
