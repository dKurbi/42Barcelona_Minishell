/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:33:46 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/16 15:30:49 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// comprueba si las comillas son pares desde i hasta end
// si end = -1, prueba hasta el final del string
// si comillas estan bien - return 1, si comillas son impares - return -1
// y devuelve 0 si no tiene comillas
int	is_quotes_pair(char *str, int i, int end)
{
	char	quote;
	char	dquote;
	char	is_quote;

	is_quote = 0;
	quote = 1;
	dquote = 1;
	if (end == -1)
		end = ft_strlen(str) - 1;
	while (str[i] && i <= end)
	{
		if ((str[i] == QUOTE || str[i] == DQUOTE) && !is_quote)
			is_quote = 1;
		if (str[i] == QUOTE && dquote == 1)
			quote *= -1;
		if (str[i] == DQUOTE && quote == 1)
			dquote *= -1;
		i++;
	}
	return (quote * dquote * is_quote);
}

//devuelve la pos de la proxima comilla simple o doble (se pasa como arg)
// a partir de un numero i y devuelve -1 si no hay otra comilla
int	where_next_quote_is(char *str, char quote, int i)
{
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

// devuelve la posicion de la proxima comilla (simple o doble) desde una pos i
// si no noo hay comillas devuelve -1
int	where_next_any_quote_is(char *str, int i)
{
	int	quote_pos;
	int	rtn;

	quote_pos = where_next_quote_is(str, QUOTE, i);
	rtn = where_next_quote_is(str, DQUOTE, i);
	if ((quote_pos == -1 && rtn == -1) || \
		(quote_pos == -1 && rtn > -1) || (rtn != -1 && rtn < quote_pos))
		return (rtn);
	else
		rtn = quote_pos;
	return (rtn);
}

void	strtrim_quotes_pipe(t_msh *msh, t_line *copy_line, char	*str_strtrim)
{
	t_pipe	*copy_pipe;

	copy_pipe = msh->lst_pipe;
	while (copy_pipe != NULL)
	{
		copy_line = copy_pipe->lst_line;
		while (copy_line != NULL)
		{
			if (if_quote_start_final(copy_line->str) == QUOTE)
				str_strtrim = ft_strtrim(copy_line->str, "\'");
			else if (if_quote_start_final(copy_line->str) == DQUOTE)
				str_strtrim = ft_strtrim(copy_line->str, "\"");
			if (str_strtrim != NULL)
			{
				free(copy_line->str);
				copy_line->str = ft_strdup(str_strtrim);
			}
			free_str(&str_strtrim);
			copy_line = copy_line->next;
		}
		copy_pipe = copy_pipe->next;
	}
}

void	strtrim_quotes_all(t_msh *msh)
{
	t_line	*copy_line;
	char	*str_strtrim;

	copy_line = NULL;
	str_strtrim = NULL;
	if (msh->lst_pipe != NULL)
	{
		strtrim_quotes_pipe(msh, copy_line, str_strtrim);
		return ;
	}
	copy_line = msh->lst_line;
	while (copy_line != NULL)
	{
		if (if_quote_start_final(copy_line->str) == QUOTE)
			str_strtrim = ft_strtrim(copy_line->str, "\'");
		else if (if_quote_start_final(copy_line->str) == DQUOTE)
			str_strtrim = ft_strtrim(copy_line->str, "\"");
		if (str_strtrim != NULL)
		{
			free(copy_line->str);
			copy_line->str = ft_strdup(str_strtrim);
		}
		free_str(&str_strtrim);
		copy_line = copy_line->next;
	}
}
