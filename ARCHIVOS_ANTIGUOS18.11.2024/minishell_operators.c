/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_operators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:22:36 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/10 19:51:01 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//check <<, >, etc.
int	check_operators(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && i < (int)ft_strlen(str))
	{
		if (str[i] == QUOTE || str[i] == DQUOTE)
			i = where_next_quote_is(str, str[i], i + 1) + 1;
		while (str[i] && str[i] != QUOTE \
			&& str[i] != DQUOTE && str[i] != IPUT_RED && str[i] != OPUT_RED)
			i++;
		if (str[i] == IPUT_RED || str[i] == OPUT_RED)
			return (1);
	}
	return (0);
}

void	decide_operators(char *str, int i, t_line **lst_line)
{
	if (str[i] && (str[i] == IPUT_RED) && \
		str[i + 1] && str[i] == str[i + 1])
		add_new_line_node(ft_strdup("<<"), TYPE_HDC, lst_line);
	else if (str[i] && (str[i] == OPUT_RED) && \
		str[i + 1] && str[i] == str[i + 1])
		add_new_line_node(ft_strdup(">>"), TYPE_APND, lst_line);
	else if (str[i] && (str[i] == OPUT_RED))
		add_new_line_node(ft_strdup(">"), TYPE_OPUT_RED, lst_line);
	else if (str[i] && (str[i] == IPUT_RED))
		add_new_line_node(ft_strdup("<"), TYPE_IPUT_RED, lst_line);
}

//para pasar de <<EOF a EOF (por ejemplo)
int	skip_operators(char *str, int i)
{
	if (str[i] && str[i + 1] && (str[i + 1] == str[i]))
		return (i + 2);
	return (i + 1);
}

void	addstr_to_lst_line(char *str, t_line **lst_line, int i)
{
	int		last;
	char	*sub_str;

	if (check_operators(str) == 0)
	{
		add_new_line_node(str, decide_type(str), lst_line);
		return ;
	}
	sub_str = NULL;
	while (str[i] && i < (int)ft_strlen(str))
	{
		last = i;
		while (str[last] && str[last] != IPUT_RED && str[last] != OPUT_RED)
			last++;
		if (str[i] != IPUT_RED && str[i] != OPUT_RED)
		{
			sub_str = ft_substr(str, i, last - i);
			add_new_line_node(sub_str, decide_type(sub_str), lst_line);
		}
		decide_operators(str, last, lst_line);
		i = skip_operators(str, last);
	}
	free_str(&str);
}
