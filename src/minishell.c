/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/19 18:00:28 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//esto tendremos que eliminar despues, esto es solo para comprobar si esta bien estructura
void	PRINT_lst_line(t_msh *msh)
{
	t_line	*copy_lst;

	if (!msh->lst_line)
		return ;
	copy_lst = msh->lst_line;
	while (copy_lst)
	{
		printf("lst_line->read_line = %s\n", copy_lst->str);
		printf("lst_line->type = %d\n\n", copy_lst->type + '0') ;
		copy_lst = copy_lst->next;
	}
}

void	PRINT_split_line(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		printf("%s\n",str[i++]);
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
		add_history(msh->read_line);
		if (is_quotes_pair(msh->read_line, 0, -1) != -1)
		{
			PRINT_split_line(ft_split_pipe(msh->read_line));
			if (check_pipe_in_word(msh->read_line))
				msh->lst_pipe = new_pipe_list(msh);
			else
				msh->lst_line = new_line_list(msh);
		}
		else
			write(2, ERR_QUOTE, ft_strlen(ERR_QUOTE));

		PRINT_lst_line(msh);//para printear

		free(msh->read_line);
		free(msh->lst_line);
		printf("\n");
	}
	free_msh(&msh);
	return (0);
}
