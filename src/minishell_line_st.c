/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_line_st.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/12/16 03:49:44 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

t_line	*new_line_list(t_msh *msh, char *str)
{
	int		i;
	char	is_quotes;
	t_line	*lst_line;

	if (!str || !msh)
		return (NULL);
	i = 0;
	lst_line = NULL;
	is_quotes = is_quotes_pair(str, 0, -1);
	if (!is_quotes)
		lst_line = new_list_without_quotes(str, &lst_line, msh);
	else if (is_quotes == 1)
		lst_line = new_list_with_quotes(str, msh);
	else
	{
		append_until_required(str, QUOTE);//aqui tenemos que hacer append hasta el caracter que necesita (falta)
		new_line_list(msh, str);
	}
	return (lst_line);
}

t_line *new_list_without_quotes(char *str, t_line **lst_line, t_msh *msh)//aqui tendremos pipe tambien
{
	char	**line;
	int		i;
	int		word_last_pos;

	word_last_pos = 0;
	i = 0;
	line = ft_split(str, ' ');
	if (!line)
		exit_error(ERR_MALLOC);
	while (line[i])
	{
		if (check_pipe_in_word(line[i]))
		{
			msh->pipe_active = 1;
			if (ft_strlen(line[i]) != 1)
				pipe_divide_word(line[i], lst_line);
		}
		else
			add_new_line_node(line[i], TYPE_STR, lst_line);
		i++;
	}
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

t_line	*new_list_with_quotes(char *str, t_msh *msh)
{
	int 	i;
	t_line 	*new_list;
	char 	*text;
	int		w_q_is;
	int		w_q_is_next;
	char 	which_act_quote;
	int		word_last_pos;

	if (!str)
		return (NULL);
	i = 0;
	new_list = NULL;
	text = NULL;
	w_q_is = 0;
	w_q_is_next = 0;
	which_act_quote = '\0';
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
			add_new_line_node(text, TYPE_STR, new_list);
		}
		else
		{
			word_last_pos = calculate_last_pos_word(str, i);
			text = ft_substr(str, i, word_last_pos);
			if (check_pipe_in_word(text))//NO ESTA TESTEADO: hacer un check si tenemos |
			{
				msh->pipe_active = 1;
				if (ft_strlen(text) != 1)
					pipe_divide_word(text, &new_list);//NO ESTA TESTEADO:dividir nuestra palabra y anadir ahi nuestros textos (si tenemos ls|cat|ls|cat o ls|cat o | por ejemplos)
			}
			else
				add_new_line_node(text, TYPE_STR, new_list);
			i = word_last_pos;//hacer un skip para empezar en nueva palabra, por abajo tenemos i++
		}
		free_str(&text);
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