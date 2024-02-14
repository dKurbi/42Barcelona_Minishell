/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:03:50 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/14 14:14:04 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_change_var_in_env(char ***ev, char *var, int if_in_ev)
{
	int	i;

	i = 0;
	while (i != if_in_ev)
		i++;
	free_str(&(*ev)[i]);
	(*ev)[i] = var;
}

char	**export_append_to_env(t_msh *msh, char **old_ev, char *var)
{
	char	**new_env;
	int		i;

	if (check_var_equal(var))
	{
		free_str(&var);
		return (old_ev);
	}
	new_env = (char **) malloc(sizeof(char *) * (export_len_env(old_ev) + 2));
	if (!new_env)
		print_error_exit(&msh, ERR_MALLOC);
	i = 0;
	while (old_ev[i])
	{
		new_env[i] = old_ev[i];
		i++;
	}
	new_env[i++] = var;
	new_env[i] = NULL;
	free(old_ev);
	return (new_env);
}

void	builtin_export_no_plus(t_msh *msh, char *var, int i)
{
	int	if_in_ev;

	if_in_ev = -1;
	if_in_ev = if_var_in_env(msh, ft_substr(var, 0, len_before_equal(var)));
	if (if_in_ev >= 0)
		export_change_var_in_env(&msh->ev, \
								ft_strdup(msh->exec.exec_arg[i]), if_in_ev);
	else
		msh->ev = export_append_to_env(msh, msh->ev, \
										ft_strdup(msh->exec.exec_arg[i]));
}

int	builtin_export_add_all(t_msh *msh)
{
	int		i;
	char	*var;
	int		exit_status;

	exit_status = 0;
	i = 0;
	while (msh->exec.exec_arg[++i])
	{
		var = export_create_var(msh, i);
		if (check_var_equal(var))
		{
			exit_status = 1;
			print_warning_with_3_arg("export", msh->exec.exec_arg[i], \
									ERR_INV_INDENT);
		}
		if (check_plus_before_equal(msh->exec.exec_arg[i]))
			builtin_export_plus(msh, i);
		else
			builtin_export_no_plus(msh, var, i);
		free_str(&var);
	}
	return (exit_status);
}

//export - print as env or add a variable in env
int	builtin_export(t_msh *msh)
{
	if (!msh->exec.exec_arg[1])
		builtin_export_print_all(msh);
	else
	{
		if (builtin_export_add_all(msh))
			return (1);
	}
	return (0);
}
