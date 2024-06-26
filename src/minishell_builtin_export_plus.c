/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export_plus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:30:49 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/12 20:10:33 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//A+=E == A=E
char	*get_var_no_plus(char *var)
{
	char	*new_var;
	int		i;
	int		len;
	int		j;
	int		flag;

	flag = 0;
	len = (int)ft_strlen(var);
	new_var = (char *) malloc(sizeof(char) * (len + 1));
	if (!new_var)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len && var[j])
	{
		if (var[j] == '+' && var[j + 1] == '=' && !flag)
		{
			j++;
			flag++;
		}
		else
			new_var[i++] = var[j++];
	}
	new_var[i] = '\0';
	return (new_var);
}

void	export_join_old_new_content(char ***ev, char *var, int if_in_ev)
{
	int		i;
	char	*content_from_var;

	i = 0;
	while (i != if_in_ev)
		i++;
	content_from_var = ft_strdup(ft_strchr(var, '=') + 1);
	free_str(&var);
	if (!content_from_var)
		return ;
	(*ev)[i] = get_ft_strjoin_modif((*ev)[i], content_from_var);
	free_str(&content_from_var);
}

void	builtin_export_plus(t_msh *msh, int i)
{
	int		if_in_ev;
	char	*var_no_plus;

	var_no_plus = get_var_no_plus(msh->exec.exec_arg[i]);
	if (!var_no_plus)
		print_error_exit(&msh, ERR_MALLOC);
	if_in_ev = if_var_in_env(msh, ft_strdup(var_no_plus));
	if (if_in_ev >= 0)
		export_join_old_new_content(&msh->ev, var_no_plus, if_in_ev);
	else
		msh->ev = export_append_to_env(msh, msh->ev, var_no_plus);
}
