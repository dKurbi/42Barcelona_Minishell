/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:06:52 by iassambe          #+#    #+#             */
/*   Updated: 2023/10/19 20:14:55 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_inc/pipex_bonus.h"

/*
CHILD PROCESS: while() loop: pid == 0;
We should do all previous process before
doing the final (parent) processing;
Ex.: < infile command1 | command2 | ... (until commandFINAL);
*/
void	px_child(t_info **info, int i)
{
	close((*info)->pip[0]);
	if (dup2((*info)->fd1, STDIN_FILENO) < 0 || \
		dup2((*info)->pip[1], STDOUT_FILENO) < 0)
	{
		px_print_error((*info), 6, -1);
		infofree(info, 1);
	}
	close((*info)->fd1);
	close((*info)->pip[1]);
	px_handle_child(info, i);
	if (execve((*info)->cmd, (*info)->exe_arg, (*info)->ev) < 0)
	{
		px_print_error((*info), 5, -1);
		infofree(info, 1);
	}
}

/*
PARENT PROCESS: after while() ;
From child processes, We should write
the result to our fd2 duplicated;
From example: | commandFIN > outfile;
*/
void	px_parent(t_info **info, int i_last)
{
	if (access((*info)->av[i_last + 1], F_OK) < 0 || (*info)->fd2 < 0)
	{
		px_print_error(*info, 1, i_last + 1);
		infofree(info, 0);
		exit(127);
	}
	if (dup2((*info)->fd2, STDOUT_FILENO) < 0 || \
		dup2((*info)->fd1, STDIN_FILENO) < 0)
	{
		px_print_error(*info, 6, -1);
		infofree(info, 1);
	}
	close((*info)->fd1);
	close((*info)->fd2);
	px_handle_parent(info, i_last);
	if (execve((*info)->cmd, (*info)->exe_arg, (*info)->ev) < 0)
	{
		px_print_error((*info), 5, -1);
		infofree(info, 1);
	}
}

//i - through cmds, i_last - last cmd;
void	px_pipex_bonus(t_info *info, int i, int i_last)
{
	if (access(info->av[1], F_OK) < 0 || info->fd1 < 0)
		px_print_error(info, 1, 1);
	while (++i < i_last)
	{
		if (pipe(info->pip) < 0)
			infofree(&info, 1);
		info->proc = fork();
		if (info->proc < 0)
			px_print_error(info, 2, -1);
		if (info->proc == 0)
			px_child(&info, i);
		close(info->fd1);
		info->fd1 = info->pip[0];
		close(info->pip[1]);
	}
	if (i == i_last)
		px_parent(&info, i_last);
	waitpid(info->proc, 0, 0);
}

int	main(int argc, char **av, char **ev)
{
	t_info	*info;

	if (argc < 5)
		exit(EXIT_FAILURE);
	info = infonew(av, ev, argc);
	if (!info)
		infofree(&info, 1);
	px_manage_av_cmds(info);
	px_pipex_bonus(info, 1, info->ac - 2);
	infofree(&info, 0);
	return (0);
}
