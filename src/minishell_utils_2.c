/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:05:19 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/10 05:39:27 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	calculate_len_lst_line(t_line *lst_line)
{
	int		len;
	t_line	*copy_lst;

	len = 0;
	copy_lst = lst_line;
	while (copy_lst != NULL)
	{
		if (!is_redirection(copy_lst->type))
			len++;
		else
			copy_lst = copy_lst->next;
		if (copy_lst)
			copy_lst = copy_lst->next;
	}
	return (len);
}

//calculate everything that is not a delimiter and return the POSITION
int	calculate_last_pos_word(char *str, int i)
{
	if (!str)
		return (0);
	while (str[i] && str[i] != ' ' && str[i] != '\t' \
			&& str[i] != QUOTE && str [i] != DQUOTE)
		i++;
	return (i);
}

//remove quotes
char	*strtrim_str_quotes(char *str)
{
	char	*new_str;

	if (str[0] == QUOTE && str[ft_strlen(str) - 1] == QUOTE)
		new_str = ft_strtrim(str, "\'");
	else if (str[0] == DQUOTE && str[ft_strlen(str) - 1] == DQUOTE)
		new_str = ft_strtrim(str, "\"");
	else
		new_str = ft_strdup(str);
	free_str(&str);
	return (new_str);
}

int	decide_type_redirection(char *str, int redir_in_quotes)
{
	int	if_is_redir;

	if_is_redir = 0;
	if (str[0] == '<' && str[1] == '<')
		if_is_redir = TYPE_HDC;
	else if (str[0] == '>' && str[1] == '>')
		if_is_redir = TYPE_APND;
	else if (str[0] == IPUT_RED)
		if_is_redir = TYPE_IPUT_RED;
	else if (str[0] == OPUT_RED)
		if_is_redir = TYPE_OPUT_RED;
	if (if_is_redir && redir_in_quotes)
		return (TYPE_STR);
	else if (if_is_redir && !redir_in_quotes)
		return (if_is_redir);
	return (0);
}

//return the type of string
int		decide_type(char *str, int redir_in_quotes)
{
	if (!str)
		return (-1);
	if (str[0] == '-' || (str[0] == '-' && str[1] == '-'))
		return (TYPE_FLG);
	else if ((str[0] == QUOTE && str[ft_strlen(str) - 1] == QUOTE) || \
				(str[0] == DQUOTE && str[ft_strlen(str) - 1] == DQUOTE))
		return (TYPE_STR);
	else if (decide_type_redirection(str, redir_in_quotes))
		return (decide_type_redirection(str, redir_in_quotes));
	else
		return (TYPE_CMD);
}
