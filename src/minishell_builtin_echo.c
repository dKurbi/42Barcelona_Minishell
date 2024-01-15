/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_echo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 04:03:05 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/15 17:19:20 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_echo_loop(t_msh *msh, int i, int flag_status)
{
	char	*echo_str;

	if ((flag_status == 1 && i != 2) || (flag_status == 0 && i >= 2))
		printf(" ");
	if (msh->exec.exec_arg[i][0] == QUOTE && \
		msh->exec.exec_arg[i][ft_strlen(msh->exec.exec_arg[i]) - 1] == QUOTE)
		echo_str = ft_strtrim(msh->exec.exec_arg[i], "\'");
	else if (msh->exec.exec_arg[i][0] == DQUOTE && \
		msh->exec.exec_arg[i][ft_strlen(msh->exec.exec_arg[i]) - 1] == DQUOTE)
		echo_str = ft_strtrim(msh->exec.exec_arg[i], "\"");
	else
		echo_str = ft_strdup(msh->exec.exec_arg[i]);
	if (!echo_str)
		print_error_exit(&msh, ERR_MALLOC);
	printf("%s", echo_str);
	free_str(&echo_str);
}

int	builtin_echo(t_msh *msh)
{
	int		i;
	int		flag_status;

	flag_status = 0;
	i = 0;
	if (msh->exec.exec_arg[1] && !ft_strncmp(msh->exec.exec_arg[1], "-n", 2) \
	&& ft_strlen(msh->exec.exec_arg[1]) == 2)
	{
		flag_status = 1;
		i++;
	}
	while (msh->exec.exec_arg[++i])
		builtin_echo_loop(msh, i, flag_status);
	if (flag_status == 0)
		printf("\n");
	return (0);
}
