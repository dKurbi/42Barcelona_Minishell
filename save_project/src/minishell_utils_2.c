/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:05:19 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/08 20:41:30 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	calculate_len_lst_line(t_line *lst_line)
{
	int		len;
	t_line	*copy_lst;

	len = 0;
	copy_lst = lst_line;
	while (copy_lst != NULL)
	{
		if (!is_redirection(copy_lst->type))
			len++;
		else
			copy_lst = copy_lst->next;
		if (copy_lst)
			copy_lst = copy_lst->next;
	}
	return (len);
}

//como en el split,  aqui calcular todo que no es delim. y return la POSICION
int	calculate_last_pos_word(char *str, int i)
{
	if (!str)
		return (0);
	while (str[i] && str[i] != ' ' && str[i] != '\t' \
			&& str[i] != QUOTE && str [i] != DQUOTE)
		i++;
	return (i);
}
