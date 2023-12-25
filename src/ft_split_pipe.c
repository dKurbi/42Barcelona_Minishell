/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:36:11 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/25 04:45:55 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_split_leninword(char *s, int i)
{
	int	init;
	int	minus_space;

	minus_space = 0;
	init = i;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
	{
		i++;
		minus_space++;
	}
	while (s[i] && s[i] != PIPE)
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] == QUOTE || s[i] == DQUOTE)
			i = where_next_quote_is(s, s[i], i + 1) + 1;
		else if (s[i] != PIPE)
			i++;
	}
	i--;
	while (s[i] != '\0' && i >= 0 && (s[i] == ' ' || s[i] == '\t'))
		i--;
	return (i - init - minus_space + 1);
}

size_t	ft_split_words(char *s)
{
	ssize_t	i;
	size_t	numwords;

	i = 0;
	numwords = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] == PIPE)
		{
			numwords++;
			i++;
		}
		while (s[i] == QUOTE || s[i] == DQUOTE)
			i = where_next_quote_is(s, s[i], i + 1) + 1;
		while (s[i] && s[i] != ' ' && s[i] != '\t' \
				&& s[i] != PIPE && s[i] != QUOTE && s[i] != DQUOTE)
			i++;
		if (s[i] == '\0')
			numwords++;
	}
	return (numwords);
}

static char	**ft_split_fail(char **splited)
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

char	**ft_split_loop(char *s, char **splited, size_t i, size_t j)
{
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		/* printf("our &s - %s\n", &s[i]);
		printf("our ft_split_leninword - %i\n", ft_split_leninword(s, i));
		printf("our i - %li\n", i); */
		splited[j] = ft_substr(s, i, ft_split_leninword(s, i));
		if (splited[j] == NULL)
			return (ft_split_fail(splited));
		i = i + ft_split_leninword(s, i) + 1;
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		i++;
		j++;
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
	return (ft_split_loop(s, splited, 0, 0));
}
