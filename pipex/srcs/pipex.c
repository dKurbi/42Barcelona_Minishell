/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:44:57 by iassambe          #+#    #+#             */
/*   Updated: 2023/10/19 20:27:58 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
CHILD PROCESS: pid == 0 (is zero);
We should do all previous process before
doing the final (parent) processing;
From example: < infile command1 |;
*/
void	px_child(t_info **info)
{
	if (dup2((*info)->fd1, STDIN_FILENO) < 0 || \
		dup2((*info)->pip[1], STDOUT_FILENO) < 0)
	{
		px_print_error((*info), 6, -1);
		return ;
	}
	close((*info)->pip[0]);
	close((*info)->fd1);
	px_handle_child(info, 2);
	if (execve((*info)->cmd, (*info)->exe_arg, (*info)->ev) < 0)
	{
		px_print_error((*info), 5, -1);
		infofree(info, 1);
	}
}

/*
PARENT PROCESS (pid > 0 || pid >= 1);
From child process, We should write
the result to our new file in fd2;
From example: | command2 > outfile;
*/
void	px_parent(t_info **info)
{
	if (access((*info)->av[4], F_OK) < 0 || (*info)->fd2 < 0)
	{
		px_print_error(*info, 1, 4);
		infofree(info, 0);
		exit(127);
	}
	else
	{
		if (dup2((*info)->fd2, STDOUT_FILENO) < 0 || \
			dup2((*info)->pip[0], STDIN_FILENO) < 0)
		{
			px_print_error(*info, 6, -1);
			return ;
		}
		close((*info)->pip[1]);
		close((*info)->fd2);
		px_handle_parent(info, 3);
		if (execve((*info)->cmd, (*info)->exe_arg, (*info)->ev) < 0)
		{
			px_print_error((*info), 5, -1);
			infofree(info, 1);
		}
	}
}

void	px_pipex(t_info *info)
{
	if (pipe(info->pip) < 0)
		infofree(&info, 1);
	if (access(info->av[1], F_OK) < 0 || info->fd1 < 0)
		px_print_error(info, 1, 1);
	info->proc = fork();
	if (info->proc < 0)
		px_print_error(info, 2, -1);
	if (info->proc == 0)
		px_child(&info);
	else if (info->proc > 0)
		px_parent(&info);
	waitpid(-1, 0, 0);
}

int	main(int argc, char **av, char **ev)
{
	t_info	*info;

	if (argc != 5)
		exit(EXIT_FAILURE);
	info = infonew(av, ev);
	if (!info)
		infofree(&info, 1);
	px_manage_av(&info);
	px_pipex(info);
	infofree(&info, 0);
	return (0);
}
