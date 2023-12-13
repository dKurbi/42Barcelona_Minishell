/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_line_st.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/13 20:41:10 by iassambe         ###   ########.fr       */
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

//como en el split, pero por aqui calcular todo que no es delimitador y devolver la POSICION
int	calculate_last_pos_word(char *str, int i)
{
	if (!str)
		return (0);
	while (str[i] && str[i] != ' ' && str[i] != '\t')//cuando no tenemos espacio o tab
		i++;
	return (i);
}

t_line	*new_list_with_quotes(char *str)
{
	int 	i;
	t_line 	*new_list;
	char 	*text;
	int		w_q_is;
	int		w_q_is_next;
	char 	which_act_quote;
	int		word_last_pos;

	new_list = NULL;
	i = 0;
	w_q_is = 0;
	text = NULL;
	word_last_pos = 0;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		
		w_q_is = where_next_any_quote_is(str, i);
		if (w_q_is == i)
		{
			which_act_quote = str[w_q_is];
			w_q_is_next = where_next_quote_is(str, which_act_quote, w_q_is + 1);
			text = ft_substr(str, i, w_q_is_next);
			if (!text)
				exit_error(ERR_MALLOC);
			//anadir al t_line nuestra palabra correctamente
		}
		else
		{
			word_last_pos = calculate_last_pos_word(str, i);
			text = ft_substr(str, i, word_last_pos);
			if (check_pipe_in_word(text))//NO ESTA ACABADO: hacer un check si tenemos |
			{
				pipe_divide_word(text, &new_list);//NO ESTA ACABADO:dividir nuestra palabra y anadir ahi nuestros textos (si tenemos ls|cat|ls|cat o ls|cat o | por ejemplos)
			}
			else
			{
				//NO ESTA ACABADO: anadir al t_line nuestra palabra que no tiene casos especiales
			}
			i = word_last_pos;//hacer un skip para empezar en nueva palabra, por abajo tenemos i++
		}
		
		
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
