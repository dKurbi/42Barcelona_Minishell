/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:26:14 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/28 20:16:33 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

void	handle_signal_heredoc(int sign, siginfo_t *sa, void *data)
{
	t_msh	*msh;

	(void)(sa);
	msh = (t_msh *) data;
	if (sign == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		exit(1);
	}
}

void	handle_nothing(int sign, siginfo_t *sa, void *data)
{
	(void) sa;
	(void) data;
	(void) sign;
}

void	handle_signal_main(int sign, siginfo_t *sa, void *data)
{
	(void)(sa);
	(void)(data);

	if (sign == SIGINT)
	{
		g_exit_status = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signal_exec_mode(int sign, siginfo_t *sa, void *data)
{
	(void)(data);
	(void)(sa);
	if (sign == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		exit(130);
	}
	if (sign == SIGQUIT)
	{
		printf("\n");
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		exit(131);
	}
}

void	signal_control_heredoc(t_msh *msh)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handle_signal_heredoc;
	if (sigaction(SIGINT, &sa, (void *) msh) == -1)
		print_error_exit(&msh, ERR_SIG);
	if (sigaction(SIGQUIT, &sa, (void *) msh) == -1)
		print_error_exit(&msh, ERR_SIG);
}

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

void	signal_control_block(t_msh *msh)
{
	(void)(msh);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}