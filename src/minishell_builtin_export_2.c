/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:35:26 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/06 19:14:39 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	export_len_env(char **ev)
{
	int	len;

	len = 0;
	while (ev[len] != NULL)
		len++;
	return (len);
}

//returns len before '='
int	len_before_equal(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len])
	{
		if (str[len] == '=')
			return (len + 1);
		len++;
	}
	return (len);
}

int	export_create_var_len(t_msh *msh, int i)
{
	int	len;
	int	minus_quote;

	minus_quote = 0;
	len = 0;
	while (msh->exec.exec_arg[i][len])
	{
		if (msh->exec.exec_arg[i][len] == QUOTE)
			minus_quote++;
		else if (msh->exec.exec_arg[i][len] == DQUOTE)
			minus_quote++;
		len++;
	}
	return (len - minus_quote);
}

//int i isfrom msh->exec.exec_arg
char	*export_create_var(t_msh *msh, int i)
{
	int		j;
	int		iter_var;
	char	*var;

	j = export_create_var_len(msh, i);
	var = (char *) malloc(sizeof(char) * (j + 1));
	if (!var)
		print_error_exit(&msh, ERR_MALLOC);
	j = 0;
	iter_var = 0;
	while (msh->exec.exec_arg[i][j])
	{
		if (msh->exec.exec_arg[i][j] != QUOTE && \
			msh->exec.exec_arg[i][j] != DQUOTE)
			var[iter_var++] = msh->exec.exec_arg[i][j];
		j++;
	}
	var[iter_var] = '\0';
	return (var);
}
