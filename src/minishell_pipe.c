/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:55:11 by iassambe          #+#    #+#             */
/*   Updated: 2023/12/16 03:32:04 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//1 - pipe, 0 - no pipe
int	check_pipe_in_word(char *str)
{
	if ((ft_strlen(str) == 1 && str[0] == PIPE) || (ft_strchr(str, PIPE)))
		return (1);
	else
		return (0);
}

/* dividr cuando pipe:
pipe|ls|pipe = pipe ls pipe
pipe| ls = pipe ls
ls |pipe = ls pipe
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
	while (str[i])
	{
		bef_pipe = i;
		while (str[i] && str[i] != PIPE)
			bef_pipe++;
		if (bef_pipe == 0)//protegemos si tenemos ls |pipe
			i++;
		else
		{
			divided_str = ft_substr(str, i, bef_pipe);
			if (!divided_str)
				exit_error(ERR_MALLOC);
			add_new_line_node(divided_str, TYPE_STR, lst_line);
			free_str(&divided_str);
			i = bef_pipe + 1;
		}
	}
}