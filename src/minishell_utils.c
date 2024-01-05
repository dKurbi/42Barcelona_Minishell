/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:11:47 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/05 18:06:39 by iassambe         ###   ########.fr       */
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

//el ultimo t_line del total
t_line	*ft_lst_line_last(t_line *lst)
{
	t_line	*lastlist;

	if (lst == NULL)
		return (NULL);
	lastlist = lst;
	while (lastlist->next != NULL)
		lastlist = lastlist->next;
	return (lastlist);
}
