/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/16 16:52:14 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

int	g_exit_status;

#endif

void	free_main_loop(t_msh *msh)
{
	free_str(&msh->read_line);
	free_lst_line(&msh->lst_line);
	free_lst_pipe(&msh->lst_pipe);
	free_exec(&msh->exec);
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
	strtrim_quotes_all(msh);
	return (0);
}

		///DEBUG to main (drag with OPTION+arrow down)

/* 		PRINT_comillas(msh->read_line);
		printf("\n\nDEBUG PRINTS:\n\n");
		PRINT_lst_line(msh->lst_line);
		PRINT_lst_pipe(msh->lst_pipe); */
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
	while (1)
	{
		signal_control_main(msh);
		msh->read_line = readline("Minishell-> ");
		if (initial_check(msh))
			break ;
		if (preparing_commands(msh) != 1)
			execution(msh);
		free_main_loop(msh);
	}
	rl_clear_history();
	free_msh(&msh);
	return (g_exit_status);
}
