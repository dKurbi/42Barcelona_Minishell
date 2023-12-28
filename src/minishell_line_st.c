/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_line_st.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:29:07 by iassambe          #+#    #+#             */
/*   Updated: 2023/12/28 05:29:47 by iassambe         ###   ########.fr       */
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
	printf("status newlstline1\n");
	is_quotes = is_quotes_pair(read_line, 0, -1);
	if (!is_quotes)
		lst_line = new_lst_without_quotes(msh, &lst_line, read_line);
	else if (is_quotes == 1)
		lst_line = new_lst_with_quotes(msh, &lst_line, read_line);
	printf("status newlstline2\n");
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
	while (split_line[++i])//ft strdup porque esta mal free_double_str (tambe hace free en t_line*)
		add_new_line_node(ft_strdup(split_line[i]), \
						decide_type(split_line[i]), lst_line);
	free_double_str(&split_line);
	return (*lst_line);
}

int	new_lst_decide(t_line **lst_line, char *rline, int i, int last)//WARNING!!! CAMBIAR FUNCION
{
	char	*text;//rename to str

	text = NULL;
	if (rline[i] == QUOTE || rline[i] == DQUOTE)
	{
		text = ft_substr(rline, i, \
					where_next_quote_is(rline, rline[i], i + 1) - i + 1);//WARN: change to: text = str_create_special_case(text)  for: ls<<EOF
		if (!text)
			return (-1);
		add_new_line_node(text, TYPE_STR, lst_line);
		i = where_next_quote_is(rline, rline[i], i + 1) + 1;
	}
	else
	{
		text = ft_substr(rline, i, last - i);
		if (!text)
			return (-1);
		add_new_line_node(text, decide_type(text), lst_line);
		i = last;
	}
	return (i);
}

//crear t_line con comillas (echo->'string1'->"string2") (cat->"archivo|archivo")
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
		i = new_lst_decide(lst_line, rline, i, last);
		if (i < 0)
			print_error_exit(&msh, ERR_MALLOC);
	}
	return (*lst_line);
}

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
