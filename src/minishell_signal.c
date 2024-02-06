/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:26:14 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/02/06 19:57:19 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

//catch signals when doing heredoc
void	signal_control_heredoc(t_msh *msh)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handle_signal_heredoc;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_exit(&msh, ERR_SIG);
	signal(SIGQUIT, SIG_IGN);
}

//catch signals when executing commands
void	signal_control_exec(t_msh *msh)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handle_signal_exec_mode;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_exit(&msh, ERR_SIG);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		print_error_exit(&msh, ERR_SIG);
}

//catch signals for main
void	signal_control_main(t_msh *msh)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handle_signal_main;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_exit(&msh, ERR_SIG);
	signal(SIGQUIT, SIG_IGN);
}

//blocking signals
void	signal_control_block(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
