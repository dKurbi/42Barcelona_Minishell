/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:34:49 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/03 13:23:11 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*clean_var(char *str)
{
	int		i;
	char	*rtn;
	int		len;

	i = 0;
	len = ft_strlen(str);
	rtn = NULL;
	while (str[i] && str[i] != ' ' && str[i] != DQUOTE)
	{
		i++;
		if (str[i] == '$')
			break ;
	}
	if (len == i)
		return (ft_strdup(str));
	rtn = ft_substr(str, 0, i);
	return (rtn);
}

char	*expand(char *var, t_msh *msh)
{
	int		i;
	int		len;
	char	*rtn;
	char	*sub_str;

	var = clean_var(var);
	rtn = ft_strdup("\0");
	if (var[0] == '$' && var[1] && var[1] != '?')
	{
		len = ft_strlen(var);
		sub_str = ft_substr(var, 1, len - 1);
		free(var);
		var = get_ft_strjoin_modif(sub_str, "=");
		i = -1;
		printf("expand bef while\n");
		while (msh->ev[++i])
		{
			if (ft_strncmp(msh->ev[i], var, len) == 0)
			{
				printf("expand loop\n");
				free(var);
				free(rtn);
				rtn = ft_substr(msh->ev[i], len, ft_strlen(msh->ev[i]) - len + 1);
				return (rtn);
			}
		}
	}
	else if (var[0] == '$' && var[1] == '?')
	{
		free_3_str(&var, &rtn, NULL);
		rtn = ft_itoa(msh->exit_status);
	}
	free_str(&var);
	return (rtn);
}

int	where_is_dollar(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*case_dollar(char *str, t_msh *msh)
{
	int		dp;
	char	*txt[2];
	char	*rtn;

	dp = where_is_dollar(str, 0);
	txt[0] = ft_substr(str, 0, dp);
	if (!txt[0])
		return (NULL);
	txt[1] = expand(&str[dp], msh);
	if (!txt[1])
	{
		free(txt[0]);
		return (NULL);
	}
	rtn = ft_strjoin(txt[0], txt[1]);
	free_3_str(&txt[0], &txt[1], &str);
	return (rtn);
}

char	*case_dollar_with_quotes(char *str, t_msh *msh)
{
	char	*rtn;
	char	*add_join;
	char	*aux[2];
	int		i;
	int		dp;

	i = 0;
	add_join = NULL;
	rtn = NULL;
	aux[1] = NULL;
	while (str[i])
	{
		printf("str\n");
		dp = where_is_dollar(str, i);
		if (dp != -1)
		{
			printf("if str\n");
			aux[0] = ft_substr(str, i, dp - i);
			printf("if substr\n");
			aux[1] = expand(&str[dp], msh);
			printf("if expand\n");
			add_join = get_ft_strjoin_modif(aux[0], aux[1]);
			printf("if get_join\n");
			i = dp + 1;
			while (str[i] && str[i]!= ' ' && str[i] != '\t' && str[i] != '\"' && str[i] != '$')
				i++;
		}
		else
		{
			printf("else str\n");
			add_join = ft_substr(str, i, ft_strlen(str));
			i = ft_strlen(str);
		}
		printf("joinrtn\n");
		rtn = get_ft_strjoin_modif(rtn, add_join);
		printf("free addjoin str\n");
		free(add_join);
		printf("free aux1 str\n");
		free_str(&aux[1]);
	}
	printf("OUT\n");
	free_str(&str);
	return (rtn);
}
