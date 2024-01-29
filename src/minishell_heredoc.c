/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:50:51 by iassambe          #+#    #+#             */
/*   Updated: 2024/01/29 04:30:26 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	write_herdoc(t_msh *msh, t_line *copy, int hcd_pip)
{
	char	*line;

	signal_control_heredoc(msh);
	line = NULL;
	line = readline("> ");
	while (ft_strncmp(line, copy->next->str, ft_strlen(copy->next->str)) \
			|| ft_strlen(line) != ft_strlen(copy->next->str))
	{
		ft_putstr_fd(line, hcd_pip);
		ft_putchar_fd('\n', hcd_pip);
		free_str(&line);
		line = readline("> ");
	}
	free_str(&line);
	ft_close(hcd_pip); 
	exit (0);
}

static void	init_fwh(int *nb, int *hdc_pip, int *hdc_status, t_msh *msh)
{
	if (msh->exec.fd_here_doc[0] != -1)
		ft_close(msh->exec.fd_here_doc[0]);
	if (pipe(msh->exec.fd_here_doc) == -1)
		print_error_exit(&msh, ERR_PIPE);
	*nb = 1;
	*hdc_status = 0;
	if (pipe(hdc_pip) < 0)
		print_error_exit(&msh, ERR_PIPE);
}

static void	close_fd(int *fd)
{
	ft_close(fd[1]);
	ft_close(fd[0]);
}

int	fork_write_herdoc(t_msh *msh, t_line *line_copy)
{
	pid_t	hdc_proc;
	int		hdc_pip[2];
	int		hdc_status;
	int		nb;

	init_fwh(&nb, hdc_pip, &hdc_status, msh);
	hdc_proc = fork();
	if (hdc_proc < 0)
		print_error_exit(&msh, ERR_FORK);
	if (hdc_proc == 0)
	{
		close_fd(msh->exec.fd_here_doc);
		close(hdc_pip[0]);
		exit(write_herdoc(msh, line_copy, hdc_pip[1]));
	}
	ft_close(hdc_pip[1]);
	waitpid(hdc_proc, &hdc_status, 0);
	if (WIFEXITED(hdc_status))
		hdc_status = WEXITSTATUS(hdc_status);
	close_fd(msh->exec.fd_here_doc);
	dup2(hdc_pip[0], msh->exec.fd_here_doc[0]);
	ft_close(hdc_pip[0]);
	return (hdc_status);
}

int	check_heredoc(t_msh *msh)
{
	t_line	*line_copy;
	int		heredoc_status;

	heredoc_status = 0;
	line_copy = msh->lst_line;
	while (line_copy)
	{
		if (line_copy->type == TYPE_HDC)
		{
			heredoc_status = fork_write_herdoc(msh, line_copy);
			if (heredoc_status > 0)
				return (heredoc_status);
		}
		line_copy = line_copy->next;
	}
	return (heredoc_status);
}

void	heredoc_redir(t_msh *msh)
{
	dup2(msh->exec.fd_here_doc[0], STDIN_FILENO);
	ft_close(msh->exec.fd_here_doc[0]);
}
