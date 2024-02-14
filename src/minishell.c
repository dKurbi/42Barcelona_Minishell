/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/14 14:37:02 by dkurcbar         ###   ########.fr       */
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
	return (0);
}

int	main(int ac, char **av, char **ev)
{
	t_msh	*msh;

	msh = NULL;
	pre_init_check(&msh, ac, av, ev);
	g_exit_status = 0;
	while (1)
	{
		signal_control_main(msh);
		msh->read_line = readline("Minishell-> ");
		if (msh->read_line && (msh->read_line[0] == '\0' \
			|| check_ifempty_str(msh->read_line) == 1))
		{
			free_str(&msh->read_line);
			continue ;
		}
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
