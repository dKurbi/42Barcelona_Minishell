/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:39:10 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/06 09:54:21 by iassambe         ###   ########.fr       */
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
		free_lst_pipe(&(*msh)->lst_pipe);
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
		ft_close(&(*lst_pipe)->fd_heredoc[0]);
		ft_close(&(*lst_pipe)->fd_heredoc[1]);
		free(*lst_pipe);
		*lst_pipe = copy_lst;
	}
	*lst_pipe = NULL;
}

void	free_exec(t_exec *exec)
{
	ft_close(&exec->fd_stdin);
	ft_close(&exec->fd_stdout);
	if (exec->dir)
		closedir(exec->dir);
	free_double_str(&exec->exec_arg);
	close_int_arr(exec->even_pip);
	close_int_arr(exec->odd_pip);
	free_3_str(&exec->cmd_no_path, &exec->cmd_with_path, &exec->path);
}

void	exit_free_child(t_msh *msh, int exit_status)
{
	ft_close(&msh->exec.pip[0]);
	ft_close(&msh->exec.pip[1]);
	free_msh(&msh);
	rl_clear_history();
	exit(exit_status);
}
