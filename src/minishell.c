/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/08 20:29:39 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



void	free_main_loop(t_msh *msh)
{
	free_str(&msh->read_line);
	free_lst_line(&msh->lst_line);
	free_lst_pipe(&msh->lst_pipe);
}

int	preparing_commands(t_msh *msh)
{
	if (is_quotes_pair(msh->read_line, 0, -1) != -1)
	{
		if (check_pipe_in_word(msh->read_line))
			msh->lst_pipe = new_lst_pipe(msh);
		else
			msh->lst_line = new_lst_line(msh, msh->read_line);
	}
	else
	{
		print_warning(ERR_QUOTE);
		return (1);
	}
	if (check_syntax(msh))
	{
		print_warning(ERR_SYNTAX);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **ev)
{
	t_msh	*msh;

	if (ac != 1)
		print_error_exit(NULL, ERR_AC);
	(void)(av);
	msh = mshnew(ev);
	if (!msh)
		print_error_exit(NULL, ERR_MALLOC);
	g_exit_status = 0;
	signal_control_main(msh);
	while (1)
	{
		msh->read_line = readline("Minishell-> ");
		if (initial_check(msh))
			break ;
		if (preparing_commands(msh) != 1)
			execution(msh);

		char **exe_arg = get_exec_argv(msh, msh->lst_line);
		
		PRINT_split_line(exe_arg);
			
		PRINT_comillas(msh->read_line);
		PRINT_lst_line(msh->lst_line);
		PRINT_lst_pipe(msh->lst_pipe);
		free_main_loop(msh);
	}
	free_msh(&msh);
	return (0);
}
