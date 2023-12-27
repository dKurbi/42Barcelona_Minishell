/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_line_st.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:29:07 by iassambe          #+#    #+#             */
/*   Updated: 2023/12/27 05:35:16 by iassambe         ###   ########.fr       */
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
	/*else if (is_quotes == 1)
		lst_line = new_lst_with_quotes(msh, &lst_line, read_line);*/
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

//crear t_line con comillas (echo->'string1'->"string2") (cat->"archivo|archivo")
t_line	*new_lst_with_quotes(t_msh *msh, t_line **lst_line, char *rline)
{
	int		i;
	char	*text;
	int		word_last_pos;

	i = 0;
	text = NULL;
	word_last_pos = 0;
	while (rline[i] != '\0' && i < (int)ft_strlen(rline))
	{
/* 		while (rline[i] && rline[i] == ' ' || rline[i] == '\t')
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
		i++; */
		
		while (rline[i] && (rline[i] == ' ' || rline[i] == '\t'))
			i++;
		word_last_pos = i;
		while (rline[i] && (rline[i] != QUOTE && rline != DQUOTE))
			word_last_pos++;
		if (rline[i] == QUOTE || rline[i] == DQUOTE)
		{
			text = ft_substr(rline, i, \
						where_next_quote_is(rline, rline[i], i + 1) - i + 1);//NO ESTA CORRECTO!!
			if (!text)
				print_error_exit(&msh, ERR_MALLOC);
			add_new_line_node(text, TYPE_STR, &lst_line);
			i = where_next_quote_is(rline, rline[i], i + 1) + 1;
		}
		else
		{
			text = ft_substr(rline, i, word_last_pos - i + 1);//NO ESTA TESTEADO
			if (!text)
				print_error_exit(&msh, ERR_MALLOC);
			add_new_line_node(text, decide_type(text), &lst_line);
			i = word_last_pos + 1;
		}
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
