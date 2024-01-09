/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:39:10 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/09 18:56:57 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//free main t_msh
void	free_msh(t_msh **msh)
{
	if (*msh != NULL)
	{
		free_str(&(*msh)->read_line);
		free_double_str(&(*msh)->ev);
		free_exec(&(*msh)->exec);
		free_lst_line(&(*msh)->lst_line);
		free(*msh);
	}
	*msh = NULL;
}

//free t_line *
void	free_lst_line(t_line **lst_line)
{
	t_line	*copy_lst_line;

	if (*lst_line == NULL)
		return ;
	copy_lst_line = *lst_line;
	while (*lst_line != NULL)
	{
		copy_lst_line = (*lst_line)->next;
		free_str(&(*lst_line)->str);
		free((*lst_line));
		*lst_line = copy_lst_line;
	}
	*lst_line = NULL;
}

//free t_pipe*
void	free_lst_pipe(t_pipe **lst_pipe)
{
	t_pipe	*copy_lst;

	if (!*lst_pipe)
		return ;
	copy_lst = *lst_pipe;
	while (*lst_pipe != NULL)
	{
		copy_lst = (*lst_pipe)->next;
		if ((*lst_pipe) != NULL)
			free_lst_line(&(*lst_pipe)->lst_line);
		free(*lst_pipe);
		*lst_pipe = copy_lst;
	}
	*lst_pipe = NULL;
}

//esto es para que evitar norminette
void	free_3_str(char **s1, char **s2, char **s3)
{
	if (*s1 != NULL)
		free_str(s1);
	if (*s2 != NULL)
		free_str(s2);
	if (*s3 != NULL)
		free_str(s3);
}

void	free_exec(t_exec *exec)
{
	close(exec->fd_stdin);
	close(exec->fd_stdout);
	free_double_str(&exec->exec_arg);
	free_3_str(&exec->cmd_no_path, &exec->cmd_with_path, &exec->path);
}

/*
	int		pip[2];
	int		old_pip[2];
	int		fd_stdin;//nuevos variables para hacer pipes(para recibir)
	int		fd_stdout;//nuevos variables para hacer pipes(para redirigir)
	char	**exec_arg;
	char	*cmd_with_path;
	char	*cmd_no_path;
	char	*path;
	pid_t	proc;
	int		wait_status;*/