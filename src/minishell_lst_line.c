/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lst_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:32:03 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/12 16:52:37 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//-2: break; -1: malloc err; 0 and more: good
int	new_lst_loop(t_msh *msh, t_line **lst_line, t_create crt, int i)
{
	while (crt.rline[i] && (crt.rline[i] == ' ' || crt.rline[i] == '\t'))
		i++;
	if (i >= (int)ft_strlen(crt.rline))
		return (-2);
	crt.last = i;
	while (crt.rline[crt.last] && crt.rline[crt.last] != QUOTE \
	&& crt.rline[crt.last] != DQUOTE && crt.rline[crt.last] != ' ' \
	&& crt.rline[crt.last] != '\t')
		crt.last++;
	if (crt.rline[i] == QUOTE || crt.rline[i] == DQUOTE)
		i = lst_add_quotes(msh, lst_line, crt, i);
	else
		i = lst_add_str(msh, lst_line, crt, i);
	return (i);
}

//create t_line when we have quotes
t_line	*new_lst_with_quotes(t_msh *msh, t_line **lst_line, char *rline)
{
	int			i;
	t_create	create;

	i = 0;
	create.rline = rline;
	create.in_quotes = 0;
	while (rline[i] != '\0' && i < (int)ft_strlen(rline))
	{
		create.last_l = NULL;
		i = new_lst_loop(msh, lst_line, create, i);
		if (i < 0 && i == -2)
			break ;
		else if (i < 0 && i == -1)
			print_error_exit(&msh, ERR_MALLOC);
	}
	return (*lst_line);
}

//create t_line when we don't have quotes
t_line	*new_lst_without_quotes(t_msh *msh, t_line **lst_line, char *rline)
{
	char	**split_line;
	int		i;

	split_line = ft_split(rline, ' ');
	if (!split_line)
		print_error_exit(&msh, ERR_MALLOC);
	i = -1;
	while (split_line[++i])
	{
		if (ft_strchr(split_line[i], '$') != NULL)
			split_line[i] = case_dollar(split_line[i], msh);
		else if (ft_strchr(split_line[i], '~') != NULL)
			split_line[i] = case_home(split_line[i], msh);
		if (!split_line[i])
			print_error_exit(&msh, ERR_MALLOC);
		addstr_to_lst_line(split_line[i], lst_line, REDIR_NO_QUOTES, 0);
	}
	free(split_line);
	return (*lst_line);
}

//create a lst_line and decide if it is with/without quotes
t_line	*new_lst_line(t_msh *msh, char *read_line)
{
	char	is_quotes;
	t_line	*lst_line;

	if (!msh || !msh->read_line || !read_line)
		return (NULL);
	lst_line = NULL;
	if (read_line[0] == '\0')
	{
		add_new_line_node(ft_strdup(""), \
						decide_type("", REDIR_NO_QUOTES), &lst_line);
		return (lst_line);
	}
	is_quotes = is_quotes_pair(read_line, 0, -1);
	if (!is_quotes)
		lst_line = new_lst_without_quotes(msh, &lst_line, read_line);
	else if (is_quotes == 1)
		lst_line = new_lst_with_quotes(msh, &lst_line, read_line);
	return (lst_line);
}
