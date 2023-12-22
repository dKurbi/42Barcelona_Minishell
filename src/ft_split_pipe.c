/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:36:11 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/22 20:19:36 by iassambe         ###   ########.fr       */
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
			i = where_next_quote_is(s, s[i], i + 1) + 1;
		else
			i++;
	}
	return (i - init);
}

size_t	ft_split_words(char *s)
{
	ssize_t	i;
	size_t	numwords;

	i = 0;
	numwords = 0;
	while (s[i])
	{
		/*
		while (s[i] && s[i] != QUOTE && s[i] != DQUOTE && s[i] != PIPE)
			i++;
		printf("split words: %s\n", &s[i]);
		if (s[i] == QUOTE || s[i] == DQUOTE)
			i = where_next_quote_is(s, s[i], i + 1) + 1;
		else 
		{
			numwords++;
			if (s[i] == '\0')
				break ;
			i++;
		}
		if (s[i] == '\0')
			break ;
		
		*/
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] == PIPE)
		{
			numwords++;
			i++;
		}
		else if (s[i] == QUOTE || s[i] == DQUOTE)
			i = where_next_quote_is(s, s[i], i + 1) + 1;
		else
		{
			while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != PIPE)
				i++;
			if (s[i] == PIPE)
			{
				numwords++;
				i++;
			}
		}
		if (s[i] == '\0')
			numwords++;
		
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
			printf("ft_split_pipe: ft_split_loop: splitted [j]: %s\n", splited[j]);
			if (!splited[j++])
				return (ft_split_fail(splited));
			s = s + ft_split_leninword(s, i);
		}
		else
			s++;
	}

/* 	while (s[i])
	{
		
	} */

	
	splited[j] = NULL;
	return (splited);
}

char	**ft_split_pipe(char *s)
{
	char	**splited;
	size_t	words;

	if (!s)
		return (NULL);
	printf("\n\ns a la entrada de ft_split_pipe: %s\n", s);
	printf("and len - %zu\n", ft_strlen(s));
	words = ft_split_words(s);
	printf("ft_split_pipe: ft_split_pipe: words: %zu\n", words);
	splited = (char **)malloc(sizeof(char *) * (words + 1));
	if (splited == NULL)
		return (NULL);
	return (ft_split_loop(s, splited));
}
