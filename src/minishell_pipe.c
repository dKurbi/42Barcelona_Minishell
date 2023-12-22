/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:55:11 by iassambe          #+#    #+#             */
/*   Updated: 2023/12/22 03:15:20 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//return: 1 - pipe, 0 - no pipe
int	check_pipe_in_word(char *str)
{
	int	i;

	if (is_quotes_pair(str, 0, -1) == 0)
	{
		if (ft_strchr(str, PIPE) != NULL)
			return (1);
	}
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		while (str[i] != QUOTE && str[i] != DQUOTE)
		{
			if (str[i] == PIPE)
				return (1);
			i++;
		}
		i = where_next_quote_is(str, str[i], i + 1) + 1;
	}
	return (0);
}

/* dividr cuando pipe:
pipe|ls|pipe = pipe | ls | pipe
pipe| ls = pipe | ls
ls |pipe = ls | pipe
pipe|ls| = pipe ls */
void	pipe_divide_word(char *str, t_line **lst_line)
{
	int		i;
	int		bef_pipe;
	char	*divided_str;

	if (str == NULL)
		return ;
	i = 0;
	bef_pipe = 0;
	divided_str = NULL;
	if (str[i] == PIPE)
	{
		add_new_line_node(STR_PIPE, decide_type(STR_PIPE), lst_line);
		i++;
	}
	while (str[i])
	{
		printf("i in pipe_divide_word - %d, befPipe - %d\n", i, bef_pipe);
		bef_pipe = i;
		while (str[bef_pipe] && str[bef_pipe] != PIPE)
			bef_pipe++;
		printf("i in pipe_divide_word - %d, befPipe - %d\n", i, bef_pipe);
		divided_str = ft_substr(str, i, bef_pipe);
		if (!divided_str)
			exit_error(ERR_MALLOC);
		add_new_line_node(divided_str, decide_type(divided_str), lst_line);
		i = bef_pipe + 1;
	}
}

void	addback_lst_pipe(t_msh *msh, t_pipe **lst_pipe, char *str)
{
	t_pipe	*copy_lst;

	if (!*lst_pipe)
	{
		*lst_pipe = (t_pipe *) malloc(sizeof(t_pipe));
		if (!*lst_pipe)
			exit_error(ERR_MALLOC);
		(*lst_pipe)->lst_line = new_lst_line(msh, str);
		(*lst_pipe)->next = NULL;
		return ;
	}
	copy_lst = *lst_pipe;
	while (copy_lst->next != NULL)
		copy_lst = copy_lst->next;
	copy_lst->next = (t_pipe *) malloc(sizeof(t_pipe));
	if (!copy_lst->next)
		exit_error(ERR_MALLOC);
	copy_lst->next->lst_line = new_lst_line(msh, str);
	copy_lst->next->next = NULL;
}


t_pipe	*new_lst_pipe(t_msh *msh)
{
	char	**split_pipe;
	int		i;
	t_pipe	*lst_pipe;

	msh->pipe_active = 1;
	split_pipe = ft_split_pipe(msh->read_line);
	if (!split_pipe)
		return (NULL);
	i = -1;
	lst_pipe = NULL;
	while (split_pipe[++i])
	{
		addback_lst_pipe(msh, &lst_pipe, split_pipe[i]);
	}
	free_double_str(&split_pipe);
	return (lst_pipe);
}
