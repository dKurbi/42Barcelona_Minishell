/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:06:46 by iassambe          #+#    #+#             */
/*   Updated: 2023/10/19 20:17:06 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_inc/pipex_bonus.h"

/*
pip[2] - for pipe() fds; av - **argv; ev - **env; 
exe_arg - 2nd pos in execve(?, exe_arg, ?);
cmd - fullpath command (/bin/ls, /usr/bin/cat); 
raw_cmd - only command (ls, cat); fd1 - first file;
fd2 - second file; proc - pid_t chi/par for fork();
ac - argc;
*/
t_info	*infonew(char **av, char **ev, int ac)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->av = av;
	info->ev = ev;
	info->exe_arg = NULL;
	info->cmd = NULL;
	info->raw_cmd = NULL;
	info->fd1 = open(av[1], O_RDONLY);
	info->fd2 = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	info->proc = -1;
	info->ac = ac;
	return (info);
}

/*
free our struct *t_info;
flag: 1 - exit(FAILURE);
*/
void	infofree(t_info **info, int flag)
{
	if (*info != NULL)
	{
		px_free_string(&(*info)->cmd);
		px_free_string(&(*info)->raw_cmd);
		px_free_split(&(*info)->exe_arg);
		free(*info);
	}
	*info = NULL;
	if (flag == 1)
		exit(EXIT_FAILURE);
}

/*
if error occurred - display (print) in stderr:
1 - fd1 or fd2 no such fi/dir; 2 - fork err;
3 - no path; 4 - no cmd; 5 - exec err;
6 - dup2 err;
*/
void	px_print_error(t_info *info, int flag, int i)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (flag == 1)
	{
		ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(info->av[i], STDERR_FILENO);
	}
	else if (flag == 2)
		ft_putstr_fd("fork error", STDERR_FILENO);
	else if (flag == 3)
		ft_putstr_fd("path not found", STDERR_FILENO);
	else if (flag == 4)
	{
		ft_putstr_fd(info->av[i], STDERR_FILENO);
		ft_putstr_fd(": command not found", STDERR_FILENO);
	}
	else if (flag == 5)
		ft_putstr_fd("execute error", STDERR_FILENO);
	else if (flag == 6)
		ft_putstr_fd("duplicate error", STDERR_FILENO);
	if (flag > 0)
		ft_putstr_fd("\n", STDERR_FILENO);
}

//create info->exe_arg;
void	px_create_execve_args(t_info **info, int i)
{
	(*info)->exe_arg = ft_split((*info)->av[i], ' ');
	free((*info)->exe_arg[0]);
	(*info)->exe_arg[0] = ft_strdup((*info)->cmd);
}
