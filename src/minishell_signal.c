/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:26:14 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/10 04:20:13 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

void	handle_signal(int sign, siginfo_t *sa, void *data)
{
	(void)(sa);
	(void)(data);
	if (sign == SIGINT)
	{
		g_exit_status = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sign == SIGQUIT)
	{
		g_exit_status = 131;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_control_main(t_msh *msh)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handle_signal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_exit(&msh, ERR_SIG);
	signal(SIGQUIT, SIG_IGN);
}
