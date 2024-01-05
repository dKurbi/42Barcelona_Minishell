/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_getter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:56:35 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/05 18:05:49 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/* 
char	*get_raw_cmd(t_msh *msh)
{
	
}

char	*get_cmd(t_msh *msh)
{
	
}
*/

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
		exe_arg[i] = ft_strdup(copy_lst->str);
		if (exe_arg[i++] == NULL)
			return (ft_split_free(exe_arg));
		copy_lst = copy_lst->next;
	}
	exe_arg[i] = NULL;
	return (exe_arg);
}