/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:39:10 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/13 16:52:35 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_str(char **str)
{
	if (*str != NULL)
		free(*str);
	*str = NULL;
}

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

void	free_lst_line(t_line **lst)
{
	t_line	*copy_lst;

	if (*lst == NULL)
		return ;
	copy_lst = *lst;
	while (*lst != NULL)
	{
		copy_lst = (*lst)->next;
		free_str(&(*lst)->str);
		free((*lst));
		*lst = copy_lst;
	}
	*lst = NULL;
}