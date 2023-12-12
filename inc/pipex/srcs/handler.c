/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:12:25 by iassambe          #+#    #+#             */
/*   Updated: 2023/10/19 20:33:54 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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
void	px_handle_parent(t_info **info, int i)
{
	if (px_check_ifempty((*info)->av[i]) == 1)
		exit(EXIT_FAILURE);
	px_find_cmd(info, i);
	if (!(*info)->cmd)
	{
		px_print_error((*info), 4, i);
		infofree(info, 0);
		exit(127);
	}
	px_create_execve_args(info, i);
}
