/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_metacaracters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:28:00 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/19 18:34:47 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int is_meta_or_quotes(char c)
{
	if (c == ' ' || c == '\t')
		return (SPACE_OR_TAB);
	if (c == '>' || c == '<')
		return (OPERATOR);
	if (c == QUOTE)
		return (QUOTE);
	if (c == DQUOTE)
		return (DQUOTE);
	return (OTHER_CHAR);
}

int advance_pos_until(char *str, int i, int len, char c)
{

	while(str[i])
	{
		if (is_meta_or_quotes(str[i]) == DQUOTE)
			i += where_next_quote_is(str, DQUOTE, i) + 1;
		else if (is_meta_or_quotes(str[i]) == QUOTE)
			i += where_next_quote_is(str, QUOTE, i) + 1; 
		else if  (is_meta_or_quotes(str[i]) != c)
			return (i);
		i++;
		if (i >= len)
			break;
	}
	return (len - 1);
}
static int count_word(char *str)
{
	int	i;
	int	wc;
	int	len;
	int	c;

	i = 0;
	wc = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		c = is_meta_or_quotes(str[i]);
		if (c == QUOTE || c == DQUOTE)
			i = where_next_quote_is(str, c, i) + 1; 
		if (c == OTHER_CHAR)
		{
			i = advance_pos_until(str, i, len, OTHER_CHAR);
			wc++;
		}
		else if(c == SPACE_OR_TAB)
			i = advance_pos_until(str, i, len, SPACE_OR_TAB);
		else if(c == OPERATOR)
		{
			if (i < (len -1) && is_meta_or_quotes(str[i + 1]) == OPERATOR)
				i++;
			wc++;
		}		
	}	
	return(wc);
}
	
/* 
char **ft_split_metacaracters(char *str)
{
	char	**rtn;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while ((str[i]))
	{
		
	}
	
} */
int main(int argc, char **argv)
{
	if (argc > 1)
	{
		printf ("el string '%s' tiene %d palabras\n", argv[1], count_word(argv[1]));
	}

}