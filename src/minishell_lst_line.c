/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lst_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:32:03 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/03 20:32:05 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//crear t_line con todo el contenido despues de separar de read_line
t_line	*new_lst_line(t_msh *msh, char *read_line)
{
	char	is_quotes;
	t_line	*lst_line;

	if (!msh || !msh->read_line || !read_line)
		return (NULL);
	lst_line = NULL;
	if (read_line[0] == '\0')
	{
		add_new_line_node(ft_strdup(""), decide_type(""), &lst_line);
		return (lst_line);
	}
	is_quotes = is_quotes_pair(read_line, 0, -1);
	if (!is_quotes)
		lst_line = new_lst_without_quotes(msh, &lst_line, read_line);
	else if (is_quotes == 1)
		lst_line = new_lst_with_quotes(msh, &lst_line, read_line);
	return (lst_line);
}

//crear t_line sin comillas (cat -> << -> EOF) (echo->$PATH)
t_line	*new_lst_without_quotes(t_msh *msh, t_line **lst_line, char *rline)
{
	char	**split_line;
	int		i;

	split_line = ft_split(rline, ' ');
	if (!split_line)
		print_error_exit(&msh, ERR_MALLOC);
	i = -1;
	while (split_line[++i])
	{
		if (ft_strchr(split_line[i], '$') != NULL)
			split_line[i] = case_dollar(split_line[i], msh);
		addstr_to_lst_line(ft_strdup(split_line[i]), lst_line);
	}
	free_double_str(&split_line);
	return (*lst_line);
}

int	new_lst_with_quotes_decide(t_msh *msh, t_line **lst_line, char *rline, int i, int last)
{
	char	*str;

	str = NULL;
	if (rline[i] == QUOTE || rline[i] == DQUOTE)
	{
		str = ft_substr(rline, i, \
					where_next_quote_is(rline, rline[i], i + 1) - i + 1);
		if (!str)
			return (-1);
		if (ft_strchr(str, '$') != NULL && rline[i] == DQUOTE)
			str = case_dollar_with_quotes(str, msh);
		addstr_to_lst_line(str, lst_line);
		i = where_next_quote_is(rline, rline[i], i + 1) + 1;
	}
	else
	{
		str = ft_substr(rline, i, last - i);
		if (!str)
			return (-1);
		if (ft_strchr(str, '$') != NULL)
			str = case_dollar(str, msh);
		addstr_to_lst_line(str, lst_line);
		i = last;
	}
	return (i);
}

//crear t_line con comillas
t_line	*new_lst_with_quotes(t_msh *msh, t_line **lst_line, char *rline)
{
	int		i;
	int		last;

	i = 0;
	last = 0;
	while (rline[i] != '\0' && i < (int)ft_strlen(rline))
	{
		while (rline[i] && (rline[i] == ' ' || rline[i] == '\t'))
			i++;
		if (i >= (int)ft_strlen(rline))
			break ;
		last = i;
		while (rline[last] && rline[last] != QUOTE \
		&& rline[last] != DQUOTE && rline[last] != ' ' && rline[last] != '\t')
			last++;
		i = new_lst_with_quotes_decide(msh, lst_line, rline, i, last);
		if (i < 0)
			print_error_exit(&msh, ERR_MALLOC);
	}
	return (*lst_line);
}
