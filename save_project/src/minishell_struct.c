/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:07:57 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/09 18:55:09 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_msh	*mshnew(char **env)
{
	t_msh		*msh;
	static int	exit_status;

	msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		return (NULL);
	msh->ev = create_env(env);
	if (!msh->ev)
		print_error_exit(&msh, ERR_MALLOC);
	msh->lst_line = NULL;
	msh->lst_pipe = NULL;
	msh->read_line = NULL;
	msh->pipe_active = 0;
	exit_status = 0;
	msh->exit_status = exit_status;
	msh->parser = parsernew();
	msh->exec = execnew();
	return (msh);
}

t_parser	parsernew(void)
{
	t_parser	parser;

	parser.cmd = NULL;
	parser.path = NULL;
	parser.split_path = NULL;
	parser.split_read_line = NULL;
	parser.raw_cmd = NULL;
	return (parser);
}

t_exec	execnew(void)
{
	t_exec	exec;

	exec.fd_stdin = -1;
	exec.fd_stdout = -1;
	exec.exec_arg = NULL;
	exec.cmd_with_path = NULL;
	exec.cmd_no_path = NULL;
	exec.path = NULL;
	exec.proc = 0;
	exec.wait_status = 0;
	return (exec);
}

//anadir al final t_line nuevo a ya existe t_line **
void	add_new_line_node(char *line, int type_str, t_line **lst_line)
{
	t_line	*new_node;
	t_line	*last_node;
	t_line	*lst;

	lst = *lst_line;
	if (lst_line)
	{
		last_node = (t_line *) ft_lst_line_last((void *) lst);
		new_node = (t_line *) ft_calloc(1, sizeof(t_line));
		new_node->str = line;
		new_node->type = type_str;
		new_node->next = NULL;
		if (last_node)
			last_node->next = new_node;
		else
			*lst_line = new_node;
	}
}
