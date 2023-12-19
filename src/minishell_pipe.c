/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:55:11 by iassambe          #+#    #+#             */
/*   Updated: 2023/12/18 20:21:51 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//return: 1 - pipe, 0 - no pipe
int	check_pipe_in_word(char *str)
{
	if ((ft_strlen(str) == 1 && str[0] == PIPE) || (ft_strchr(str, PIPE)))
		return (1);
	else
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
