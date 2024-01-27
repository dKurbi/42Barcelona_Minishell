/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:26:14 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/26 20:26:16 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

void	handle_signal_heredoc(int sign, siginfo_t *sa, void *data)
{
	(void)(sa);
	t_msh *msh;

	msh = (t_msh *) data;
	printf("stdin %d\n stdout %d\n", msh->exec.fd_stdin, msh->exec.fd_stdout);
	if (sign == SIGINT)
	{
		printf("SIGINT \n");
		close(msh->exec.fd_here_doc[0]);
		close(msh->exec.fd_here_doc[1]);
		//ft_close_pointer(&msh->exec.fd_here_doc[1]);
		//ft_close_pointer(&msh->exec.fd_here_doc[0]);
		restore_redirection(msh);
		printf("msh readline - %s\n\n\n", msh->read_line);
		printf("msh str - %s\n\n\n", msh->lst_line->str);
		close(msh->exec.fd_stdin);
		close(msh->exec.fd_stdout);
		//ft_close_pointer(&msh->exec.fd_stdin);
		//ft_close_pointer(&msh->exec.fd_stdout);
		g_exit_status = 111;
		exit(g_exit_status);
	}
	else if (sign == SIGQUIT)
	{
		printf("SIGQUIT\n");
		ft_close_pointer(&msh->exec.fd_here_doc[1]);
		ft_close_pointer(&msh->exec.fd_here_doc[0]);
		restore_redirection(msh);
		ft_close_pointer(&msh->exec.fd_stdin);
		ft_close_pointer(&msh->exec.fd_stdout);
		g_exit_status = 1;
	}
}
/* void	handle_signal_heredoc(int sign)
{
	if (sign == SIGINT)
	{
		g_exit_status = 1;
		exit(g_exit_status);
	}
	else if (sign == SIGQUIT)
	{
		g_exit_status = 1;
	}
} */
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
	(void)(sa);
	(void)(data);
	if (sign == SIGINT)
	{
		g_exit_status = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
	}
	else if (sign == SIGQUIT)
	{
		g_exit_status = 131;
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

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

void	signal_control_exec(t_msh *msh)
{
	struct sigaction	sa_exec;

	sa_exec.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_exec.sa_mask);
	sa_exec.sa_sigaction = handle_signal_exec_mode;
	if (sigaction(SIGINT, &sa_exec, NULL) == -1)
		print_error_exit(&msh, ERR_SIG);
	if (sigaction(SIGQUIT, &sa_exec, NULL) == -1)
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
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction =  handle_nothing;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		print_error_exit(&msh, ERR_SIG);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		print_error_exit(&msh, ERR_SIG);
}