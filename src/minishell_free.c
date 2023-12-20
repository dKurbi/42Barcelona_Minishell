/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:39:10 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/20 01:15:35 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//free main t_msh
void	free_msh(t_msh **msh)
{
	if (*msh != NULL)
	{
		free_str(&(*msh)->read_line);
		free_lst_line(&(*msh)->lst_line);
		free(*msh);
	}
	*msh = NULL;
}

//free memoria de char *
void	free_str(char **str)
{
	if (*str != NULL)
		free(*str);
	*str = NULL;
}

//free memoria de char **
void	free_double_str(char ***double_str)
{
	int	i;

	if (*double_str == NULL)
		return ;
	i = 0;
	while ((*double_str)[i])
	{
		free_str(&(*double_str)[i]);
		i++;
	}
	free(*double_str);
	*double_str = NULL;
}

//free t_line *
void	free_lst_line(t_line **lst_line)
{
	t_line	*copy_lst_line;

	if (*lst_line == NULL)
		return ;
	copy_lst_line = *lst_line;
	while (*lst_line != NULL)
	{
		copy_lst_line = (*lst_line)->next;
		free_str(&(*lst_line)->str);
		free((*lst_line));
		*lst_line = copy_lst_line;
	}
	*lst_line = NULL;
}

void	free_lst_pipe(t_pipe **lst_pipe)
{
	t_pipe	*copy_lst;

	if (!*lst_pipe)
		return ;
	copy_lst = *lst_pipe;
	while (*lst_pipe != NULL)
	{
		copy_lst = (*lst_pipe)->next;
		free_lst_line(&(*lst_pipe)->lst_line);
		free(*lst_pipe);
		*lst_pipe = copy_lst;
	}
	*lst_pipe = NULL;
}