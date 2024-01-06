/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:36:11 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/05 17:29:23 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_split_len_word(char *s, int i)
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
	while (s[i] && s[i] != PIPE && i < (int)ft_strlen(s))
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] == QUOTE || s[i] == DQUOTE)
			i = where_next_quote_is(s, s[i], i + 1) + 1;
		else if (s[i] != PIPE && s[i] != '\0')
			i++;
	}
	i--;
	while (s[i] != '\0' && i >= 0 && (s[i] == ' ' || s[i] == '\t'))
		i--;
	return (i - init - minus_space + 1);
}

int	ft_split_calc_words(char *s)
{
	int	i;
	int	numwords;

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

char	**ft_split_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char	**ft_split_create_loop(char *s, char **split, int i, int j)
{
	while (s[i] && i < (int)ft_strlen(s))
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] == PIPE)
		{
			split[j] = ft_strdup("");
			i++;
		}
		else
		{
			split[j] = ft_substr(s, i, ft_split_len_word(s, i));
			if (split[j] == NULL)
				return (ft_split_free(split));
			i = i + ft_split_len_word(s, i) + 1;
			while (s[i] && (s[i] == ' ' || s[i] == '\t'))
				i++;
			if (s[i] == PIPE)
				i++;
		}
		j++;
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split_pipe(char *s)
{
	char	**split;
	int		words;

	if (!s)
		return (NULL);
	words = ft_split_calc_words(s);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (split == NULL)
		return (NULL);
	return (ft_split_create_loop(s, split, 0, 0));
}
