/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lst_line_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 00:40:08 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/20 01:39:48 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	lst_char_bef(t_msh *msh, t_line **lst_line, t_create crt, int i)
{

}

int	lst_add_quotes(t_msh *msh, t_line **lst_line, t_create crt, int i)
{
	char	*str;

	if (i >= 0 && crt.rline[i - 1] != ' ' && crt.rline[i - 1] != '\t')
		return (lst_char_bef(msh, lst_line, crt, i));
	str = ft_substr(rline, i, \
				where_next_quote_is(rline, rline[i], i + 1) - i + 1);
	if (!str)
		return (-1);
	if (ft_strchr(str, '$') != NULL && rline[i] == DQUOTE)
		str = case_dollar_with_quotes(str, msh);
	addstr_to_lst_line(str, lst_line, 0);
	i = where_next_quote_is(rline, rline[i], i + 1) + 1;
	return (i);
}

int	lst_add_str(t_msh *msh, t_line **lst_line, t_create crt, int i)
{
	char	*str;

	str = ft_substr(rline, i, last - i);
	if (ft_strchr(str, '$') != NULL)
		str = case_dollar(str, msh);
	addstr_to_lst_line(str, lst_line, 0);
	i = last;
	return (i);
}
