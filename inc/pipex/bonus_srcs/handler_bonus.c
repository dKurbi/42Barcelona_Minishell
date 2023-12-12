/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 02:13:05 by iassambe          #+#    #+#             */
/*   Updated: 2023/10/19 20:33:48 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_inc/pipex_bonus.h"

/*
from px_manage_av_cmds():
edit in memadress;
*/
void	px_manage_av_edit(t_info **info, int len, int i)
{
	(*info)->av[i] = px_skip_space((*info)->av[i]);
	len = ft_strlen((*info)->av[i]);
	if (len >= 2 && (*info)->av[i][0] == '\'' \
		&& (*info)->av[i][len - 1] == '\'')
	{
		ft_memmove((*info)->av[i], (*info)->av[i] + 1, len - 2);
		(*info)->av[i][len - 2] = '\0';
	}
}

/*
skip spaces;
skip first and last quotes ' ';
*/
void	px_manage_av_cmds(t_info *info)
{
	size_t	len;
	size_t	i;
	size_t	i_last;

	i = 1;
	i_last = (info->ac) - 2;
	len = 0;
	while (++i <= i_last)
	{
		len = ft_strlen(info->av[i]);
		px_manage_av_edit(&info, len, i);
	}
}

//child: prepare exe_arg and cmd for execve();
void	px_handle_child(t_info **info, int i)
{
	if (px_check_ifempty((*info)->av[i]) == 1)
		exit(EXIT_FAILURE);
	px_find_cmd(info, i);
	if (!(*info)->cmd)
	{
		px_print_error((*info), 4, i);
		infofree(info, 1);
	}
	px_create_execve_args(info, i);
}

//partent: prepare exe_arg and cmd for execve();
void	px_handle_parent(t_info **info, int i_last)
{
	if (px_check_ifempty((*info)->av[i_last]) == 1)
		exit(EXIT_FAILURE);
	px_find_cmd(info, i_last);
	if (!(*info)->cmd)
	{
		px_print_error((*info), 4, i_last);
		infofree(info, 0);
		exit(127);
	}
	px_create_execve_args(info, i_last);
}
