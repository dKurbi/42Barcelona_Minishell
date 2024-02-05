/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:05:50 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/05 16:18:17 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	calculate_len_lst_pipe(t_pipe *lst_pipe)
{
	int		len;
	t_pipe	*copy_pipe;

	len = 0;
	copy_pipe = lst_pipe;
	while (copy_pipe != NULL)
	{
		len++;
		copy_pipe = copy_pipe->next;
	}
	return (len);
}

void	change_int_arr(int *old_pip, int fd0, int fd1)
{
	ft_close(&old_pip[0]);
	ft_close(&old_pip[1]);
	old_pip[0] = fd0;
	old_pip[1] = fd1;
}

t_line	*ft_lstdup(t_line *original)
{
	t_line	*new_lst;
	t_line	*copy_original;

	if (!original)
		return (NULL);
	copy_original = original;
	new_lst = NULL;
	while (copy_original)
	{
		add_new_line_node(ft_strdup(copy_original->str), copy_original->type ,&new_lst);
		copy_original = copy_original->next;
	}
	
	return (new_lst);
}