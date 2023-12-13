/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/13 18:06:26 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int main(void)
{
	char	*str;
	t_line	*linea;
	t_line  *copy_lst;

	str = readline("prueba comillas-> ");
	while (ft_strncmp(str, "", 1))
	{ 
		printf("las comillas son %i, la primera comilla esta en %i\n", is_quotes_pair(str, 0, -1), where_next_any_quote_is(str, 0));	
		//if (!is_quotes_pair(str,0,-1))
		//{
			linea = new_line_list(str);
			copy_lst = linea;
			while (linea)
			{
				printf("linea->str = %s\n", linea->str);
				printf("linea->type = %d\n\n", linea->type + '0') ;
				linea = linea->next;
			}
		//}
		add_history(str);
		free_lst_line(&copy_lst);
		free (str);
		str = readline("prueba comillas-> ");
	}
	free_lst_line(&linea);
	free (str);
}
