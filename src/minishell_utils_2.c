/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:05:19 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/21 23:28:58 by iassambe         ###   ########.fr       */
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

char	*strtrim_str_quotes(char *str)
{
	char	*new_str;

	if (str[0] == QUOTE && str[ft_strlen(str) - 1] == QUOTE)
		new_str = ft_strtrim(str, "\'");
	else if (str[0] == DQUOTE && str[ft_strlen(str) - 1] == DQUOTE)
		new_str = ft_strtrim(str, "\"");
	else
		new_str = ft_strdup(str);
	free_str(&str);
	return (new_str);
}
