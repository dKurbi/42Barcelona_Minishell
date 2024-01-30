/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:07:57 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/30 18:56:16 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_msh	*mshnew(char **env)
{
	t_msh		*msh;

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
	msh->exec = execnew();
	return (msh);
}

t_exec	execnew(void)
{
	t_exec	exec;

	exec.old_pip_file = -1;
	exec.fd_stdin = -1;
	exec.fd_stdout = -1;
	exec.exec_arg = NULL;
	exec.cmd_with_path = NULL;
	exec.cmd_no_path = NULL;
	exec.path = NULL;
	exec.proc = -1;
	exec.fd_here_doc[0] = -1;
	exec.fd_here_doc[1] = -1;
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

//el ultimo t_line del total
t_line	*ft_lst_line_last(t_line *lst)
{
	t_line	*lastlist;

	if (lst == NULL)
		return (NULL);
	lastlist = lst;
	while (lastlist->next != NULL)
		lastlist = lastlist->next;
	return (lastlist);
}
