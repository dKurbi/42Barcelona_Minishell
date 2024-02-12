/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:05:50 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/12 18:29:27 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	calculate_len_lst_pipe(t_pipe *lst_pipe)
{
	int		len;
	t_pipe	*copy_pipe;

	len = 0;
	copy_pipe = lst_pipe;
	while (copy_pipe != NULL)
	{
		len++;
		copy_pipe = copy_pipe->next;
	}
	return (len);
}

//duplicate lst_line
t_line	*ft_lstdup(t_line *original)
{
	t_line	*new_lst;
	t_line	*copy_original;

	if (!original)
		return (NULL);
	copy_original = original;
	new_lst = NULL;
	while (copy_original)
	{
		add_new_line_node(ft_strdup(copy_original->str), \
									copy_original->type, &new_lst);
		copy_original = copy_original->next;
	}
	return (new_lst);
}

int	count_quotes_final(char *var)
{
	int	len;
	int	how_many_quotes;

	if (!var)
		return (0);
	len = ft_strlen(var) - 1;
	how_many_quotes = 0;
	while (len >= 0 && var[len] == QUOTE)
	{
		len--;
		how_many_quotes++;
	}
	return (how_many_quotes);
}

//close IF only its >=0
void	ft_close(int *fd)
{
	if (*fd < 0)
		return ;
	close(*fd);
	*fd = -1;
}

//1 - is {, |, etc..
int	ft_inquotes_case(int c)
{
	if (c == '|' || c == '>' || c == '<' || c == '{' || c == '}' \
		|| c == '(' || c == ')' || c == '*' || c == '-' || c == '+' \
		|| c == '^' || c == '=' || c == ';' || c == ':')
		return (1);
	else
		return (0);
}
