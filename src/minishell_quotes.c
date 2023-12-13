/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:33:46 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/13 17:55:33 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// comprueba si las comillas son pares desde i hasta end
// si end = -1, prueba hasta el final del string
// si las comillas estan bien, devuevle 1, si las comillas son impares  devuelve -1
// y devuelve 0 si no tiene comillas
int	is_quotes_pair(char *str, int i, int end)
{
	char	quote;
	char	dquote;
	char 	is_quote;
	
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
		if (str[i] == DQUOTE  && quote == 1 )
			dquote *= -1;
		i++;
	}
	return (quote * dquote * is_quote);
}
//devuelve la posicion de la proxima comilla simple o doble (se pasa como argumento)
// a partir de un numero i y devuelve -1 si no hay otra comill
int where_next_quote_is(char *str, char quote, int i)
{
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
	i++;
	}
	return (-1);
}

 // devuelve la posicion de la proxima comilla (simple o doble) desde una pposicion i
 // si no noo hay comillas devuelve -1
int	where_next_any_quote_is (char *str, int i)
{
	int	quote_pos;
	int	rtn;

	quote_pos = where_next_quote_is(str, QUOTE, i);
	rtn = where_next_quote_is(str, DQUOTE, i);
	if ((quote_pos == -1 && rtn == -1) || (quote_pos == -1 && rtn > -1) || (rtn != -1 && rtn < quote_pos))
		return (rtn);		
	else 
		rtn = quote_pos;
	return (rtn);
}
