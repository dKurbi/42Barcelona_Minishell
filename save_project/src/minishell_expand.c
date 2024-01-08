/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:34:49 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/08 18:46:09 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//int		g_exit_status;

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

char	*expand_dollar_ev(t_msh *msh, char *var, char *rtn, int len)
{
	char	*sub_str;
	int		i;

	sub_str = ft_substr(var, 1, len - 1);
	free_str(&var);
	var = get_ft_strjoin_modif(sub_str, "=");
	i = -1;
	while (msh->ev[++i])
	{
		if (ft_strncmp(msh->ev[i], var, len) == 0)
		{
			free(rtn);
			free_str(&var);
			rtn = ft_substr(msh->ev[i], len, ft_strlen(msh->ev[i]) - len + 1);
			break ;
		}
	}
	free_str(&var);
	return (rtn);
}

char	*expand(char *var, t_msh *msh)
{
	char	*rtn;

	var = clean_var(var);
	rtn = ft_strdup("\0");
	if (var[0] == '$' && var[1] == '\0')
		free_str(&var);
	else if (var[0] == '$' && var[1] && var[1] != '?')
		rtn = expand_dollar_ev(msh, var, rtn, ft_strlen(var));
	else if (var[0] == '$' && var[1] == '?')
	{
		free(rtn);
		free_str(&var);
		rtn = ft_itoa(g_exit_status);
	}
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
