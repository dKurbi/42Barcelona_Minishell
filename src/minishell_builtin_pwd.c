/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_pwd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:04:12 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/15 17:19:29 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_pwd(t_msh *msh)
{
	char	*current_dir;

	(void)(msh);
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		print_warning_with_arg("pwd", ERR_NO_PWD);
		return (1);
	}
	printf("%s\n", current_dir);
	free_str(&current_dir);
	return (0);
}
