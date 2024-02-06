/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:55:11 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/06 19:51:51 by dkurcbar         ###   ########.fr       */
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
	while (str[i] && i < (int)ft_strlen(str))
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		while (str[i] && str[i] != PIPE)
		{
			if (str[i] == QUOTE || str[i] == DQUOTE)
				i = where_next_quote_is(str, str[i], i + 1);
			i++;
			if (str[i] == PIPE)
				return (1);
		}
		if (str[i] == PIPE)
			return (1);
	}
	return (0);
}

//adding new lst_pipes
void	addback_lst_pipe(t_msh *msh, t_pipe **lst_pipe, char *str)
{
	t_pipe	*copy_lst;

	if (*lst_pipe == NULL)
	{
		*lst_pipe = (t_pipe *) malloc(sizeof(t_pipe));
		if (!*lst_pipe)
			print_error_exit(&msh, ERR_MALLOC);
		(*lst_pipe)->lst_line = new_lst_line(msh, str);
		(*lst_pipe)->fd_heredoc[0] = -1;
		(*lst_pipe)->fd_heredoc[1] = -1;
		(*lst_pipe)->next = NULL;
		return ;
	}
	copy_lst = *lst_pipe;
	while (copy_lst->next != NULL)
		copy_lst = copy_lst->next;
	copy_lst->next = (t_pipe *) malloc(sizeof(t_pipe));
	if (!copy_lst->next)
		print_error_exit(&msh, ERR_MALLOC);
	copy_lst->next->lst_line = new_lst_line(msh, str);
	copy_lst->next->fd_heredoc[0] = -1;
	copy_lst->next->fd_heredoc[1] = -1;
	copy_lst->next->next = NULL;
}

//create lst_pipe
t_pipe	*new_lst_pipe(t_msh *msh)
{
	char	**split_pipe;
	int		i;
	t_pipe	*lst_pipe;

	split_pipe = ft_split_pipe(msh->read_line);
	if (!split_pipe)
		return (NULL);
	i = 0;
	lst_pipe = NULL;
	while (split_pipe[i])
	{
		addback_lst_pipe(msh, &lst_pipe, split_pipe[i]);
		i++;
	}
	free_double_str(&split_pipe);
	return (lst_pipe);
}
