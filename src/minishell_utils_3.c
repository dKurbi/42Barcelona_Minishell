/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:05:50 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/03 16:53:25 by dkurcbar         ###   ########.fr       */
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
