/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:11:47 by iassambe          #+#    #+#             */
/*   Updated: 2024/02/14 13:39:00 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//1 - empty, 0 - no empty
int	check_ifempty_str(char *str)
{
	size_t	i;

	if (ft_strlen(str) == 0 || str[0] == '\0')
		return (1);
	i = 0;
	while (str && str[i] && str[i] == CHAR_SPACE)
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

void	change_exec_arg_script(t_msh *msh)
{
	char	**str;
	int		i;

	i = 0;
	while (msh->exec.exec_arg[i])
		i++;
	str = (char **) malloc(sizeof(char *) * (i + 2));
	if (str == NULL)
		print_error_exit(&msh, ERR_MALLOC);
	str[0] = ft_strdup(search_shell(msh));
	if (!str[0])
		str[0] = ft_strdup("/usr/bin/bash");
	i = -1;
	while (msh->exec.exec_arg[++i])
		str[i + 1] = ft_strdup(msh->exec.exec_arg[i]);
	str[i + 1] = NULL;
	free_double_str(&msh->exec.exec_arg);
	msh->exec.exec_arg = str;
}

char	if_quote_start_final(char *str)
{
	char	c;

	c = '\0';
	if (str[0] == QUOTE && str[ft_strlen(str) - 1] == QUOTE)
		return (QUOTE);
	if (str[0] == DQUOTE && str[ft_strlen(str) - 1] == DQUOTE)
		return (DQUOTE);
	return (c);
}

int	if_script(t_msh *msh, char *str)
{
	if (str[0] && str[1] && str[0] == POINT && str[1] == '/')
	{
		get_cmd_with_path(&msh);
		if (msh->exec.cmd_with_path)
		{
			free_str(&msh->exec.cmd_with_path);
			return (1);
		}
	}
	return (0);
}

void	print_warning_with_3_arg(char *s1, char *s2, char *s_warn)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, s1, ft_strlen(s1));
	write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, s2, ft_strlen(s2));
	write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, s_warn, ft_strlen(s_warn));
}
