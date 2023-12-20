/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:11:47 by iassambe          #+#    #+#             */
/*   Updated: 2023/12/20 17:33:27 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//1 - vacia, 0 - no vacia
int	check_ifempty_str(char *str)
{
	size_t	i;

	if (ft_strlen(str) == 0 || str[0] == '\0')
		return (1);
	i = 0;
	while (str[i] && str[i] == CHAR_SPACE)
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

//como en el split, pero por aqui calcular todo que no es delimitador y devolver la POSICION
int	calculate_last_pos_word(char *str, int i)
{
	if (!str)
		return (0);
	while (str[i] && str[i] != ' ' && str[i] != '\t' \
			&& str[i] != QUOTE && str [i] != DQUOTE)
		i++;
	return (i);
}
