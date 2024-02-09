/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:35:26 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/07 19:47:24 by iassambe         ###   ########.fr       */
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

//int i isfrom msh->exec.exec_arg
char	*export_create_var(t_msh *msh, int i)
{
	int		j;
	int		iter_var;
	char	*var;
	int		len_bef_equal;

	len_bef_equal = len_before_equal(msh->exec.exec_arg[i]);
	var = (char *) malloc(sizeof(char) * (len_bef_equal + 1));
	if (!var)
		print_error_exit(&msh, ERR_MALLOC);
	j = 0;
	iter_var = 0;
	while (j < len_bef_equal)
	{
		var[iter_var++] = msh->exec.exec_arg[i][j];
		j++;
	}
	var[iter_var] = '\0';
	return (var);
}

//return 1 - a+= (PLUS IS PLACED BEFORE =)
//return 0 - a=str+str (PLUS IS AFTER =)
int	check_plus_before_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		else if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

//print export
void	builtin_export_print_all(t_msh *msh)
{
	int	i;
	int	j;

	i = -1;
	while (msh->ev[++i])
	{
		j = -1;
		printf("declare -x ");
		while (msh->ev[i][++j] && msh->ev[i][j] != '=')
			printf("%c", msh->ev[i][j]);
		if (msh->ev[i][j])
		{
			printf("%c%c", msh->ev[i][j++], DQUOTE);
			while (msh->ev[i][j])
				printf("%c", msh->ev[i][j++]);
			printf("%c", DQUOTE);
		}
		printf("\n");
	}
}
