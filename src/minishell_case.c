/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_case.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:46:04 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/03 20:11:19 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//devuelve add_join cuando tiene dollar despues de la posicion
char	*case_quotes_next_dollar(char *str, t_msh *msh, int dp, int *i)
{
	char	*aux[2];
	char	*add_join;

	aux[0] = ft_substr(str, *i, dp - (*i));
	aux[1] = expand(&str[dp], msh);
	add_join = get_ft_strjoin_modif(aux[0], aux[1]);
	*i = dp + 1;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' \
			&& str[*i] != '\"' && str[*i] != '$')
		(*i)++;
	free_str(&aux[1]);
	return (add_join);
}

char	*case_dollar(char *str, t_msh *msh)
{
	int		dp;
	int		i;
	char	*rtn;
	char	*add_join;

	i = 0;
	rtn = NULL;
	add_join = NULL;
	while (str[i])
	{
		dp = where_is_dollar(str, i);
		if (dp != -1)
			add_join = case_quotes_next_dollar(str, msh, dp, &i);
		else
			break ;
		rtn = get_ft_strjoin_modif(rtn, add_join);
		free(add_join);
	}
	free_str(&str);
	return (rtn);
}

char	*case_dollar_with_quotes(char *str, t_msh *msh)
{
	char	*rtn;
	char	*add_join;
	int		i;
	int		dp;

	i = 0;
	add_join = NULL;
	rtn = NULL;
	while (str[i])
	{
		dp = where_is_dollar(str, i);
		if (dp != -1)
			add_join = case_quotes_next_dollar(str, msh, dp, &i);
		else
		{
			add_join = ft_substr(str, i, ft_strlen(str));
			i = ft_strlen(str);
		}
		rtn = get_ft_strjoin_modif(rtn, add_join);
		free(add_join);
	}
	free_str(&str);
	return (rtn);
}
