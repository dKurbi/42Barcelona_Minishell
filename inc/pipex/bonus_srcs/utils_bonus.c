/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:06:39 by iassambe          #+#    #+#             */
/*   Updated: 2023/10/19 20:18:33 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_inc/pipex_bonus.h"

//free char ** memadress;
void	px_free_split(char ***split)
{
	int	i;

	i = 0;
	if (!(*split))
		return ;
	while ((*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
	*split = NULL;
}

//free char * memadress;
void	px_free_string(char **s)
{
	if (!(*s))
		return ;
	free(*s);
	*s = NULL;
}

//example: make "ls -la" to "ls" or "grep BAGUET" to "grep";
char	*px_cut_bef_space(char *s)
{
	char	*new;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
		i++;
	if (i == (int)ft_strlen(s))
		return (ft_strdup(s));
	new = (char *) ft_calloc(i + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*
skips spaces without malloc();
example: "      ls" to "ls";
*/
char	*px_skip_space(char *s)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (i == 0)
		return (s);
	else
		return (s + i);
}

/*
check: "" or "   ";
return: 0 - not empty, 1 - empty;
*/
int	px_check_ifempty(char *s)
{
	size_t	i;

	if (!s)
		return (1);
	if (s[0] == '\0')
		return (1);
	i = 0;
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (i == ft_strlen(s))
		return (1);
	return (0);
}
