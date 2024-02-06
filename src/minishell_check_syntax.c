/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_check_syntax.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:33:37 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/06 19:11:09 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//if we have a parsing pipe that is not correct
int	check_pipe_empty(t_line *line)
{
	if (!line->str || (check_ifempty_str(line->str) && line->type == TYPE_CMD))
	{
		return (1);
	}
	return (0);
}

//if it is >, <<, >>, <
//1 - is redirection, 0 - not a redirection
int	is_redirection(int type)
{
	if (type >= 2 && type <= 5)
		return (1);
	return (0);
}

//check syntax only for line
int	check_syntax_line(t_line *line)
{
	t_line	*copy_line;

	copy_line = line;
	while (copy_line)
	{
		if (is_redirection(copy_line->type))
		{
			if (!copy_line->next || is_redirection(copy_line->next->type))
				return (1);
		}
		copy_line = copy_line->next;
	}
	return (0);
}

//1 - ok, 0 - error
int	check_syntax(t_msh *msh)
{
	t_pipe	*copy_pipe;

	if (msh->read_line[ft_strlen(msh->read_line) - 1] == PIPE)
		return (1);
	if (msh->lst_pipe)
	{
		copy_pipe = msh->lst_pipe;
		while (copy_pipe)
		{
			if (check_syntax_line(copy_pipe->lst_line) || \
				check_pipe_empty(copy_pipe->lst_line))
				return (1);
			copy_pipe = copy_pipe->next;
		}
	}
	else
	{
		if (check_syntax_line(msh->lst_line))
			return (1);
	}
	return (0);
}
