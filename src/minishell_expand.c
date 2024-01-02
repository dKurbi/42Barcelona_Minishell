/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:34:49 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/31 06:56:43 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char 	*clean_var(char *str)
{
	int 	i;
	char 	*rtn;
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
	rtn = ft_substr(str, 0 , i);
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
	sub_str = NULL;
	if (var[0] == '$' && var[1] != '?')
	{
		len = ft_strlen(var);
		sub_str = ft_substr(var, 1, len - 1);
		free(var);
		var = get_ft_strjoin_modif(sub_str, "=");
		i = -1;
		while (msh->ev[++i])
		{
			if (ft_strncmp(msh->ev[i], var, len) == 0)
			{
				free(rtn);
				rtn = ft_substr(msh->ev[i], len, ft_strlen(msh->ev[i]) - len + 1);
				free(var);
				return (rtn);
			}
		}
	}
	else if (var[0] == '$' && var[1] == '?')
	{
		free(var);
		free(rtn);
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
	txt[1] = expand(&str[dp], msh);
	rtn = ft_strjoin(txt[0], txt[1]);
	free_str(&txt[0]);
	free_str(&txt[1]);
	free_str(&str);
	return (rtn);
}

char	*case_dollar_with_quotes(char *str, t_msh *msh)
{
	char 	*rtn;
	char	*add_join;
	char	*aux[2];
	int 	i;
	int		dp;

	i = 0;
	rtn = NULL;
	while (str[i])
	{
		dp = where_is_dollar(str, i);
		if (dp != -1)
		{
			aux[0] = ft_substr(str, i, dp - i);
			aux[1] = expand(&str[dp], msh);
			add_join = get_ft_strjoin_modif(aux[0], aux[1]);
			i = dp + 1;
			while (str[i] && str[i]!= ' ' && str[i] != '\t' && str[i] != '\"' && str[i] != '$')
				i++;
			free_str(&aux[1]);
		}
		else
		{
			add_join = ft_substr(str, i, ft_strlen(str));
			i = ft_strlen(str);
		}
		rtn = get_ft_strjoin_modif(rtn, add_join);
		free_str(&add_join);
		free_str(&aux[1]);
	}
	free_str(&str);
	return (rtn);
}
