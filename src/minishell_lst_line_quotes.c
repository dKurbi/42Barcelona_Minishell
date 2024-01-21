/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lst_line_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 00:40:08 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/21 01:32:45 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*join_str_and_quotes(t_msh *msh, t_create crt, int i)
{
	int		iter;
	char	*res;
	int		j;

	(void)(i);
	iter = ft_strlen(crt.join);
	j = 1;
	res = (char *) malloc(sizeof(char) * \
			(ft_strlen(crt.join) + (ft_strlen(crt.str) - 2) + 1));
	if (!res)
		print_error_exit(&msh, ERR_MALLOC);
	ft_strlcpy(res, crt.join, ft_strlen(crt.join) + 1);
	while (j < where_next_quote_is(crt.str, crt.str[0], 1))
		res[iter++] = crt.str[j++];
	res[iter] = '\0';
	return (res);
}

static int	lst_char_bef(t_msh *msh, t_line **lst_line, t_create crt, int i)
{
	t_line	*last;

	last = ft_lst_line_last(*lst_line);
	crt.join = last->str;
	last->str = join_str_and_quotes(msh, crt, i);
	if (!last->str)
		return (-1);
	return (where_next_quote_is(crt.rline, crt.rline[i], i + 1) + 1);
}

int	lst_add_quotes(t_msh *msh, t_line **lst_line, t_create crt, int i)
{
	char	*str;

	str = ft_substr(crt.rline, i, \
			where_next_quote_is(crt.rline, crt.rline[i], i + 1) - i + 1);
	if (!str)
		return (-1);
	if (ft_strchr(str, '$') != NULL && crt.rline[i] == DQUOTE)
		str = case_dollar_with_quotes(str, msh);
	crt.str = str;
	if ((i - 1) >= 0 && crt.rline[i - 1] != ' ' && crt.rline[i - 1] != '\t')
		return (lst_char_bef(msh, lst_line, crt, i));
	addstr_to_lst_line(str, lst_line, 0);
	i = where_next_quote_is(crt.rline, crt.rline[i], i + 1) + 1;
	return (i);
}

int	lst_add_str(t_msh *msh, t_line **lst_line, t_create crt, int i)
{
	char	*str;

	str = ft_substr(crt.rline, i, crt.last - i);
	if (ft_strchr(str, '$') != NULL)
		str = case_dollar(str, msh);
/* 	if (i - 1 >= 0 && crt.rline[i - 1] == QUOTE || crt.rline[i - 1] == DQUOTE)
		return (lst_quotes_bef(msh, lst_line, crt, i)); */
	addstr_to_lst_line(str, lst_line, 0);
	i = crt.last;
	return (i);
}
