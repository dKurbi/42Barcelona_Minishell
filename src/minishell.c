/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/22 03:12:16 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//esto tendremos que eliminar despues, esto es solo para comprobar si esta bien estructura
void	PRINT_lst_line(t_msh *msh)
{
	t_line	*copy_lst;

	if (!msh->lst_line)
	{
		printf("NULL: lst_line\n");
		return ;
	}
	copy_lst = msh->lst_line;
	while (copy_lst)
	{
		printf("lst_line->read_line = %s\n", copy_lst->str);
		printf("lst_line->type = %d\n\n", copy_lst->type + '0') ;
		copy_lst = copy_lst->next;
	}
}


//eliminR DESPUES
void	PRINT_split_line(char **double_str)
{
	int	i;

	if (!double_str)
	{
		printf("NULL: split_line\n");
		return ;
	}
	i = 0;
	while (double_str[i])
		printf("%s\n", double_str[i++]);
}


void	PRINT_lst_pipe(t_msh *msh)
{
	t_pipe	*copy_lst;

	if (!msh->lst_pipe)
	{
		printf("NULL: lst_pipe\n");
		return ;
	}
	copy_lst = msh->lst_pipe;
	while (copy_lst)
	{
		printf("lst pipe: ");
		PRINT_lst_line(msh);
		copy_lst = copy_lst->next;
	}
}

/* int	main(int ac, char **av, char **env)
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

	if (ac != 1)
		exit_error(ERR_AC);
	(void)(av);
	msh = mshnew(ev);
	if (!msh)
		exit_error(ERR_MALLOC);
	while (1)
	{
		msh->read_line = readline("prueba comillas-> ");
		if (!msh->read_line)
			exit_error(ERR_MALLOC);
		if (!ft_strncmp(msh->read_line, "exit", 4) && \
			ft_strlen(msh->read_line) == 4)
			break ;
		
		printf("las comillas son %i, la primera comilla esta en %i\n", is_quotes_pair(msh->read_line, 0, -1), where_next_any_quote_is(msh->read_line, 0));
		if (check_ifempty_str(msh->read_line) == 0)
			add_history(msh->read_line);
		if (is_quotes_pair(msh->read_line, 0, -1) != -1)
		{
			if (check_pipe_in_word(msh->read_line))
				msh->lst_pipe = new_lst_pipe(msh);
			else
				msh->lst_line = new_lst_line(msh, msh->read_line);
		}
		else
			write(2, ERR_QUOTE, ft_strlen(ERR_QUOTE));

		PRINT_lst_line(msh);//para printear
		PRINT_lst_pipe(msh);//para printear

		printf("...check free0\n");
		free_str(&msh->read_line);
		printf("...check free1\n");
		free_lst_line(&msh->lst_line);
		printf("...check free2\n");
		free_lst_pipe(&msh->lst_pipe);
		printf("...check free3\n");
		printf("\n");
	}
	free_msh(&msh);
	return (0);
}
