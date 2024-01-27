/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:26:14 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/27 20:58:21 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#ifdef __linux__

extern int	g_exit_status;

#endif

void	handle_signal_heredoc(int sign, siginfo_t *sa, void *data)
{
	(void)(sa);
	(void) data;
	
	printf("handle signal heredoc\n");
	if (sign == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		g_exit_status = 1;
		exit(g_exit_status);
	}
	/* (void)(sa);
	t_msh *msh;

	msh = (t_msh *) data;
	printf("stdin %d\n stdout %d\n", msh->exec.fd_stdin, msh->exec.fd_stdout);
	if (sign == SIGINT)
	{
		printf("SIGINT \n");
		close(msh->exec.fd_here_doc[0]);
		close(msh->exec.fd_here_doc[1]);
		restore_redirection(msh);
		printf("msh readline - %s\n\n\n", msh->read_line);
		printf("msh str - %s\n\n\n", msh->lst_line->str);
		close(msh->exec.fd_stdin);
		close(msh->exec.fd_stdout);
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
	} */
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
	printf("handle nothing\n");
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
	//(void) data;
	printf("\n ESCUCHAAAAAAAAAA HANDL SIGNALS EXEC MODE\n\n");
	if (sign == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		g_exit_status = 130;
		exit(g_exit_status);
	}
	if (sign == SIGQUIT)
	{
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_status = 131;
		exit(g_exit_status);
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
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		print_error_exit(&msh, ERR_SIG);
	
}

void	signal_control_exec(t_msh *msh)
{
	struct sigaction	sa;

	printf("signal_control_exec\n");
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	printf("signal_control_exec SA.SA_SIGACTION\n");
	//sa.sa_sigaction = handle_signal_exec_mode;
	sa.sa_sigaction = handle_signal_exec_mode;
	printf("signal_control_exec IFS\n");
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

void bloc(int sign, siginfo_t *sa, void *data)
{
	(void)(sign);
	(void)(sa);
	t_msh *msh;
	msh = (t_msh *) data;
	printf("ESCUCHHA BLOOOOOOOOOOOOOCK, msh->exec.prop=%d\n\n", msh->exec.proc);
	 if (msh->exec.proc == 0)
	 {
		if (sign == SIGINT)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			printf("\n");
			g_exit_status = 130;
	//		exit(g_exit_status);
		}
		if (sign == SIGQUIT)
		{
			printf("Quit: 3\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			g_exit_status = 131;
	//		exit(g_exit_status);
		} 
	 }
}


void	signal_control_block(t_msh *msh, int mode)
{
	struct sigaction	sa;

	if (mode == 1)
	{
		signal_control_exec(msh);
		return ;
	}
	else if (mode == 2)
	{
		sa.sa_flags = SA_SIGINFO;
		sigemptyset(&sa.sa_mask);
		sa.sa_sigaction = bloc;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}