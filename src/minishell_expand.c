/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:34:49 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/14 01:50:26 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

//return -1 - no dollar
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

char	*clean_var(char *str)
{
	int		i;
	char	*rtn;
	int		len;

	i = 0;
	len = ft_strlen(str);
	rtn = NULL;
	if ((str[0] == '$' && str[1] && str[1] == '?'))
		return (ft_substr(str, 0, 2));
	while (str[i] && str[i] != ' ' && str[i] != DQUOTE \
			&& str[i] != QUOTE)
	{
		i++;
		if (str[i] == '$' || !ft_isalnum(str[i]))
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

char	*expand_get_rtn(t_msh *msh, char *var, char *rtn)
{
	if (var[0] == '$' && var[1] == '\0')
	{
		free_str(&rtn);
		rtn = get_ft_strjoin_modif(var, "");
	}
	else if (var[0] == '$' && var[1] == '?')
	{
		free_str(&rtn);
		free_str(&var);
		rtn = ft_itoa(g_exit_status);
	}
	else if (var[0] == '$' && var[1] && var[1] != '?')
		rtn = expand_dollar_ev(msh, var, rtn, ft_strlen(var));
	return (rtn);
}

//if we have $ in string, we need to search it in env
char	*expand(char *var, t_msh *msh)
{
	char	*rtn;
	int		case_quote_at_final;
	char	*quotes_after_dollar;

	case_quote_at_final = 0;
	quotes_after_dollar = NULL;
	var = clean_var(var);
	rtn = ft_strdup("\0");
	if (!rtn || !var)
		print_error_exit(&msh, ERR_MALLOC);
	if (var[ft_strlen(var) - 1] == QUOTE)
	{
		case_quote_at_final = count_quotes_final(var);
		var[ft_strlen(var) - case_quote_at_final] = '\0';
	}
	rtn = expand_get_rtn(msh, var, rtn);
	if (rtn != NULL && case_quote_at_final >= 1)
	{
		quotes_after_dollar = get_str_quotes(case_quote_at_final);
		rtn = get_ft_strjoin_modif(rtn, quotes_after_dollar);
		free_str(&quotes_after_dollar);
	}
	return (rtn);
}
