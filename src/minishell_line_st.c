/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_line_st.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:29:07 by iassambe          #+#    #+#             */
/*   Updated: 2023/12/22 14:02:58 by iassambe         ###   ########.fr       */
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
	is_quotes = is_quotes_pair(read_line, 0, -1);
	if (!is_quotes)
		lst_line = new_lst_without_quotes(read_line, &lst_line, msh);
	else if (is_quotes == 1)
		lst_line = new_lst_with_quotes(read_line, &lst_line, msh);
	return (lst_line);
}

//crear t_line sin comillas (cat -> << -> EOF) (echo->$PATH)
t_line	*new_lst_without_quotes(char *rline, t_line **lst_line, t_msh *msh)
{
	char	**split_line;
	int		i;

	(void)(msh);
	split_line = ft_split(rline, ' ');
	if (!split_line)
		print_error_exit(ERR_MALLOC);
	i = -1;
	while (split_line[++i])
		add_new_line_node(split_line[i], \
						decide_type(split_line[i]), lst_line);
	free_double_str(&split_line);
	return (*lst_line);
}

//crear t_line con comillas (echo->'string1'->"string2") (cat->"archivo|archivo")
t_line	*new_lst_with_quotes(char *rline, t_line **lst_line, t_msh *msh)
{
	int		i;
	char	*text;
	int		w_q_is;
	int		w_q_is_next;
	char	which_act_quote;
	int		word_last_pos;

	(void)(msh);
	i = 0;
	text = NULL;
	w_q_is = 0;
	w_q_is_next = 0;
	which_act_quote = '\0';
	word_last_pos = 0;
	while (rline[i] != '\0')
	{
		while (rline[i] == ' ' || rline[i] == '\t')
			i++;
		w_q_is = where_next_any_quote_is(rline, i);
		if (w_q_is == i)
		{
			which_act_quote = rline[w_q_is];
			w_q_is_next = where_next_quote_is(rline, which_act_quote, w_q_is + 1);
			text = ft_substr(rline, i, w_q_is_next - i + 1);
			if (!text)
				print_error_exit(ERR_MALLOC);
			add_new_line_node(text, decide_type(text), lst_line);
			i = w_q_is_next;
		}
		else
		{
			word_last_pos = calculate_last_pos_word(rline, i);
			text = ft_substr(rline, i, word_last_pos - i + 1);
			if (!text)
				print_error_exit(ERR_MALLOC);
			add_new_line_node(text, decide_type(text), lst_line);
			i = word_last_pos;
		}
		i++;
	}
	return (*lst_line);
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
