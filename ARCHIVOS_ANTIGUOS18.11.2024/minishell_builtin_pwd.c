/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_pwd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:04:12 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/16 17:24:08 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_pwd(t_msh *msh)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		print_warning_with_arg("pwd", ERR_NO_PWD);
		return (1);
	}
	else if (msh->exec.exec_arg[1] && msh->exec.exec_arg[1][0] == '-')
	{
		free_str(&current_dir);
		print_warning_with_3_arg("pwd", msh->exec.exec_arg[1], \
								ERR_BUILTIN_HAS_ARGS);
		return (1);
	}
	printf("%s\n", current_dir);
	free_str(&current_dir);
	return (0);
}
