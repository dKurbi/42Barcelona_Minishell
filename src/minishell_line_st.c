/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_line_st.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:03:41 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/13 18:28:00 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_line	*new_line_list(char *str)
{
	int		i;
	char	is_quotes;
	t_line	*lst_line;

	i = 0;
	lst_line = NULL;
	is_quotes = is_quotes_pair(str, 0, -1);
	if (!is_quotes)
		lst_line = new_list_without_quotes(str, &lst_line);
	else if (is_quotes == 1)
		lst_line = new_list_with_quotes(str);
	else
		printf("quote>\n");
	return (lst_line);
}

t_line *new_list_without_quotes(char *str, t_line ** lst_line)
{
	char	**line;
	int		i;

	i = 0;
	line = ft_split(str, ' ');
	if (!line)
		exit_error(ERR_MALLOC);
	while (line[i])
		add_new_line_node(line[i++], TYPE_STR, lst_line);
	free(line);
	return (*lst_line);
}
/*t_line	*new_list_with_quotes(char *str)
{
	int 	i;
	t_line 	*new_list;
	t_line	*copy_list;
	int		start;
	int 	end;
	char 	*text;
	int		w_q_is;

	i = 0;
	start = 0;
	end = 0;
	text = NULL;
	new_list = NULL;
	copy_list = NULL;
	w_q_is = where_next_any_quote_is(str, 0);
	if (w_q_is)
	{
		text = ft_substr(str, 0, w_q_is);
		new_list = new_list_without_quotes(text, &new_list);
	}
	free(text);
	end = where_next_quote_is(str, str[w_q_is], w_q_is + 1);
	text = ft_substr(str, w_q_is + 1, end - w_q_is - 1);
	add_new_line_node(text, str[w_q_is], &new_list);
	return (new_list);
} 
*/

t_line	*new_list_with_quotes(char *str)
{
	int 	i;
	t_line 	*new_list;
	char 	*text;
	int		w_q_is;
	int		w_q_is_next;
	char 	which_act_quote;

	new_list = NULL;
	i = 0;
	w_q_is = 0;
	text = NULL;

	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		
		w_q_is = where_next_any_quote_is(str, i);
		which_act_quote = str[w_q_is];
		w_q_is_next = where_next_quote_is(str, which_act_quote, w_q_is + 1);

		
		text = ft_strdup(str, );
		
		i++;
	}
	return (new_list);
} 
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
