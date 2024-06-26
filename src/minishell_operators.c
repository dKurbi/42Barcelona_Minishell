/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_operators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:22:36 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/12 17:21:57 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//check <<, >, etc.
//no operators - 0, operators - 1
int	check_operators(char *str)
{
	int	i;
	int	where_quote;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && i < (int)ft_strlen(str))
	{
		where_quote = 0;
		if (str[i] == QUOTE || str[i] == DQUOTE)
		{
			where_quote = where_next_quote_is(str, str[i], i + 1);
			if (where_quote < 0)
				i++;
			else
				i = where_quote + 1;
		}
		while (str[i] && str[i] != QUOTE \
			&& str[i] != DQUOTE && str[i] != IPUT_RED && str[i] != OPUT_RED)
			i++;
		if (str[i] == IPUT_RED || str[i] == OPUT_RED)
			return (1);
	}
	return (0);
}

char	*decide_operators_which_str_operator(int type)
{
	char	*which_str;

	which_str = NULL;
	if (type == TYPE_HDC)
		which_str = STR_HEREDOC;
	else if (type == TYPE_APND)
		which_str = STR_APPEND;
	else if (type == TYPE_OPUT_RED)
		which_str = STR_OUTPUT;
	else if (type == TYPE_IPUT_RED)
		which_str = STR_INPUT;
	return (which_str);
}

//add to our lst_line malloced redirections
void	decide_operators(char *str, int i, t_line **lst_line, int in_qt)
{
	char	*which_str;
	int		type;

	which_str = NULL;
	type = 0;
	if (str[i] && (str[i] == IPUT_RED) && \
		str[i + 1] && str[i] == str[i + 1])
		type = TYPE_HDC;
	else if (str[i] && (str[i] == OPUT_RED) && \
		str[i + 1] && str[i] == str[i + 1])
		type = TYPE_APND;
	else if (str[i] && (str[i] == OPUT_RED))
		type = TYPE_OPUT_RED;
	else if (str[i] && (str[i] == IPUT_RED))
		type = TYPE_IPUT_RED;
	if (type)
	{
		which_str = decide_operators_which_str_operator(type);
		if (in_qt)
			type = TYPE_STR;
		add_new_line_node(ft_strdup(which_str), type, lst_line);
	}
}

//skip operators in iteration
int	skip_operators(char *str, int i)
{
	if (str[i] && str[i + 1] && (str[i + 1] == str[i]))
		return (i + 2);
	return (i + 1);
}

//add a new str to lst_line
void	addstr_to_lst_line(char *str, t_line **lst_line, int in_qt, int i)
{
	int		last;
	char	*sub_str;

	if (check_operators(str) == 0 || (check_operators(str) == 1 && in_qt == 1))
	{
		add_new_line_node(str, decide_type(str, in_qt), lst_line);
		return ;
	}
	sub_str = NULL;
	while (i < (int)ft_strlen(str) && str[i])
	{
		last = i;
		while (str[last] && str[last] != IPUT_RED && str[last] != OPUT_RED)
			last++;
		if (str[i] != IPUT_RED && str[i] != OPUT_RED)
		{
			sub_str = ft_substr(str, i, last - i);
			add_new_line_node(sub_str, \
							decide_type(sub_str, REDIR_NO_QUOTES), lst_line);
		}
		decide_operators(str, last, lst_line, in_qt);
		i = skip_operators(str, last);
	}
	free_str(&str);
}
