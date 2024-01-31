/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:05:50 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/31 17:40:05 by iassambe         ###   ########.fr       */
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
	}
	return (len);
}
