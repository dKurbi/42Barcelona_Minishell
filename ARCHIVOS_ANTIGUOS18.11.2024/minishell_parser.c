/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:22:21 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/12 20:05:36 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	decide_type(char *str)
{
	if (!str)
		return (-1);
	if (str[0] == '-' || (str[0] == '-' && str[1] == '-'))
		return (TYPE_FLG);
	else if ((str[0] == QUOTE && str[ft_strlen(str) - 1] == QUOTE) || \
				(str[0] == DQUOTE && str[ft_strlen(str) - 1] == DQUOTE))
		return (TYPE_STR);
	else if (str[0] == '<' && str[1] == '<')
		return (TYPE_HDC);
	else if (str[0] == '>' && str[1] == '>')
		return (TYPE_APND);
	else if (str[0] == IPUT_RED)
		return (TYPE_IPUT_RED);
	else if (str[0] == OPUT_RED)
		return (TYPE_OPUT_RED);
	else
		return (TYPE_CMD);
}
