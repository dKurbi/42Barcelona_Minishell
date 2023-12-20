/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_line_st.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:29:07 by iassambe          #+#    #+#             */
/*   Updated: 2023/12/20 20:44:04 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//crear t_line con todo el contenido despues de separar de read_line
t_line	*new_lst_line(t_msh *msh)
{
	char	is_quotes;
	t_line	*lst_line;
	char 	*read_line;

	if (!msh || !msh->read_line)
		return (NULL);
	read_line = msh->read_line;
	lst_line = NULL;
	is_quotes = is_quotes_pair(read_line, 0, -1);
	if (!is_quotes)
		lst_line = new_lst_without_quotes(read_line, &lst_line, msh);
	else if (is_quotes == 1)
		lst_line = new_lst_with_quotes(read_line, msh);
	return (lst_line);
}

//crear t_line sin comillas (cat -> << -> EOF) (echo->$PATH)
t_line	*new_lst_without_quotes(char *read_line, t_line **lst_line, t_msh *msh)
{
	char	**split_line;
	int		i;

	if (!read_line)
		return (NULL);
	split_line = ft_split(read_line, ' ');
	if (!split_line)
		exit_error(ERR_MALLOC);
	i = -1;
	while (split_line[++i])
		add_new_line_node(split_line[i], \
						decide_type(split_line[i]), lst_line);
	free_double_str(&split_line);
	return (*lst_line);
}

//crear t_line con comillas (echo->'string1'->"string2") (cat->"archivo|archivo")
t_line	*new_lst_with_quotes(char *read_line, t_msh *msh)
{
	int		i;
	t_line	*new_list;
	char	*text;
	int		w_q_is;
	int		w_q_is_next;
	char	which_act_quote;
	int		word_last_pos;

	if (!read_line)
		return (NULL);
	i = 0;
	new_list = NULL;
	text = NULL;
	w_q_is = 0;
	w_q_is_next = 0;
	which_act_quote = '\0';
	word_last_pos = 0;
	while (read_line[i] != '\0')
	{
		while (read_line[i] == ' ' || read_line[i] == '\t')
			i++;
		w_q_is = where_next_any_quote_is(read_line, i);
		if (w_q_is == i)
		{
			which_act_quote = read_line[w_q_is];
			w_q_is_next = where_next_quote_is(read_line, which_act_quote, w_q_is + 1);
			text = ft_substr(read_line, i, w_q_is_next - i + 1);
			if (!text)
				exit_error(ERR_MALLOC);
			add_new_line_node(text, decide_type(text), &new_list);
			i = w_q_is_next;
		}
		else
		{
			word_last_pos = calculate_last_pos_word(read_line, i);
			text = ft_substr(read_line, i, word_last_pos - i + 1);
			add_new_line_node(text, decide_type(text), &new_list);
			i = word_last_pos;
		}
		i++;
	}
	return (new_list);
}

//anadir al final t_line nuevo a ya existe t_line **
void	add_new_line_node(char *line, int type_str, t_line **lst_line)
{
	t_line	*new_node;
	t_line	*last_node;
	t_line 	*lst;

	lst = *lst_line;
	if (lst_line)
	{
		last_node = (t_line *) ft_lst_line_last((void *) lst);
		new_node = (t_line *) ft_calloc(1, sizeof(t_line));
		new_node->str = line;
		new_node->type = type_str;
		new_node->next = NULL;
		if (last_node)
			last_node->next = new_node;
		else
			*lst_line = new_node;
	}
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
