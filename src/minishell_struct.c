/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:07:57 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/06 19:57:54 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_msh	*mshnew(char **av, char **env)
{
	t_msh		*msh;

	msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		return (NULL);
	msh->av = av;
	msh->exit_status = 0;
	msh->ev = create_env(env);
	if (!msh->ev)
		print_error_exit(&msh, ERR_MALLOC);
	msh->lst_line = NULL;
	msh->lst_pipe = NULL;
	msh->read_line = NULL;
	msh->exec = execnew();
	return (msh);
}

t_exec	execnew(void)
{
	t_exec	exec;

	exec.old_pip[0] = -1;
	exec.old_pip[1] = -1;
	exec.odd_pip[0] = -1;
	exec.odd_pip[1] = -1;
	exec.even_pip[0] = -1;
	exec.even_pip[1] = -1;
	exec.fd_stdin = -1;
	exec.fd_stdout = -1;
	exec.num_commands = 0;
	exec.exec_arg = NULL;
	exec.cmd_with_path = NULL;
	exec.cmd_no_path = NULL;
	exec.path = NULL;
	exec.proc = -1;
	exec.fd_here_doc[0] = -1;
	exec.fd_here_doc[1] = -1;
	exec.dir = NULL;
	return (exec);
}

//add a new lst_line
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

//take the last lst_line
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
