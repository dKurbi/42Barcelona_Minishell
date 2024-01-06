/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2024/01/06 19:40:41 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* 
(EL MODELO PARA HACER LUEGO)
int	main(int ac, char **av, char **env)
{
	t_msh	*msh;

	(void) av;
	if (ac != 1)
		exit_error(ERR_AC);
	msh = mshnew(env);
	if (!msh)
		exit_error(ERR_MALLOC);
	while (1)
	{
		msh->read_line = readline("Minishell$ ");
		printf("%s\n", msh->read_line);
		parser_line(msh);
		executor_line(msh);
		free(msh->read_line);
		msh->read_line = NULL;
	}
	return (0);
} */
int main(int ac, char **av, char **ev)
{
	t_msh	*msh;
	struct sigaction	sa;
	 union sigval value;
    
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(1);

	if (ac != 1)
		print_error_exit(NULL, ERR_AC);
	(void)(av);
	msh = mshnew(ev);
	value.sival_ptr = (void *) msh;
	if (!msh)
		print_error_exit(NULL, ERR_MALLOC);
	while (1)
	{
		msh->read_line = readline("Minishell-> ");
		if (initial_check(msh))//para checkear al principio
			break ;
 		if (is_quotes_pair(msh->read_line, 0, -1) != -1)
		{
			if (check_pipe_in_word(msh->read_line))
				msh->lst_pipe = new_lst_pipe(msh);
			else
				msh->lst_line = new_lst_line(msh, msh->read_line);
		}
		else
			print_warning(ERR_QUOTE); 
		if(msh->lst_pipe)
			printf("el pipe no es nulo\n");
		if (!check_syntax(msh))
		{
			printf("las comillas son %i, la primera comilla esta en %i\n\n", is_quotes_pair(msh->read_line, 0, -1), where_next_any_quote_is(msh->read_line, 0));
			printf("\n");//parte debug: printear
			PRINT_lst_line(msh->lst_line);//para printear
			PRINT_lst_pipe(msh->lst_pipe);//para printear
		}	
		else
			print_warning(ERR_SYNTAX);
		free_str(&msh->read_line);
		free_lst_line(&msh->lst_line);
		free_lst_pipe(&msh->lst_pipe);
	}
	free_msh(&msh);
	return (0);
}
