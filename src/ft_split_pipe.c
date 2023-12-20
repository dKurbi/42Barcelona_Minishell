/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:36:11 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/19 22:32:08 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_split_leninword(char *s, int i)
{
	int	init;

	init = i;
	while (s[i] && s[i] != PIPE)
	{
		if (s[i] == QUOTE || s[i] == DQUOTE)
		{
			i = where_next_quote_is(s, s[i], i + 1) + 1;
		}
		else
			i++;
	}
	return (i - init);
}

size_t	ft_split_words(char *s)
{
	size_t	i;
	size_t	numwords;

	i = 0;
	numwords = 0;
	while (s[i])
	{
		while (s[i] && s[i] != QUOTE && s[i] != DQUOTE && s[i] != PIPE)
			i++;
		if (s[i] == QUOTE || s[i] == DQUOTE)
			i = where_next_quote_is(s, s[i], i + 1) + 1;
		else 
		{
			numwords++;
			i++;
		}
		
		
		//while (str[i] && str[i] != PIPE)
		//{
		//	while (str[i] && s[i] != QUOTE && s[i] != DQUOTE && s[i] != PIPE)
		//		i++;
		//	if (s[i] == PIPE)
		//		break ;
		//	i = where_next_quote_is(s, s[i], i + 1) + 1;
		//}
		//numwords++;
		


		
	}
	return (numwords);
}

char	**ft_split_fail(char **splited)
{
	size_t	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
	return (NULL);
}

char	**ft_split_loop(char *s, char **splited)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != PIPE)
		{
			splited[j] = ft_substr(s, i, ft_split_leninword(s, i));
			if (!splited[j++])
				return (ft_split_fail(splited));
			s = s + ft_split_leninword(s, i);
		}
		else
			s++;
	}
	splited[j] = NULL;
	return (splited);
}

char	**ft_split_pipe(char *s)
{
	char	**splited;
	size_t	words;

	if (!s)
		return (NULL);
	words = ft_split_words(s);
	splited = (char **)malloc(sizeof(char *) * (words + 1));
	if (splited == NULL)
		return (NULL);
	return (ft_split_loop(s, splited));
}
