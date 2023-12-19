/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/18 20:27:38 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//esto tendremos que eliminar despues, esto es solo para comprobar si esta bien estructura
void	PRINT_lst_line(t_msh *msh)
{
	t_line	*copy_lst;

	copy_lst = msh->lst_line;
	while (copy_lst)
	{
		printf("lst_line->read_line = %s\n", copy_lst->str);
		printf("lst_line->type = %d\n\n", copy_lst->type + '0') ;
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
	msh->read_line = readline("prueba comillas-> ");
	while (ft_strncmp(msh->read_line, "", 1))
	{
		if (!ft_strncmp(msh->read_line, "exit", 4) && \
			ft_strlen(msh->read_line) == 4)
			break ;
		printf("las comillas son %i, la primera comilla esta en %i\n", is_quotes_pair(msh->read_line, 0, -1), where_next_any_quote_is(msh->read_line, 0));
		msh->lst_line = new_line_list(msh, msh->read_line);

		PRINT_lst_line(msh);//para printear

		add_history(msh->read_line);
		free(msh->read_line);
		free(msh->lst_line);
		msh->read_line = readline("prueba comillas-> ");
		printf("d\n");
	}
	free_msh(&msh);
	return (0);
}
