/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/31 14:32:56 by dkurcbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//esto tendremos que eliminar despues, esto es solo para comprobar si esta bien estructura
void	PRINT_lst_line(t_line *lst_line)
{
	t_line	*copy_lst;

	if (!lst_line)
	{
		printf("NULL: lst_line\n");
		return ;
	}
	copy_lst = lst_line;
	while (copy_lst)
	{
		printf("lst_line->read_line = %s\n", copy_lst->str);
		for (int i = 0; copy_lst->str[i]; i++)
			printf("%c and ", copy_lst->str[i]);
		printf("\n");
		printf("lst_line->type = %d\n", copy_lst->type + '0');
		printf("lst_line->type = %d\n\n", copy_lst->type);
		copy_lst = copy_lst->next;
	}
}


//eliminR DESPUES
void	PRINT_split_line(char **double_str)
{
	int	i;

	if (!double_str)
	{
		printf("NULL: SPLIT LINE **SPLIT\n");
		return ;
	}
	i = 0;
	printf("\n\nPrint split_line:\n");
	while (double_str[i])
	{
		printf("\n%s\n", double_str[i]);
		for (int j = 0; double_str[i][j]; j++)
			printf("%d and", double_str[i][j]);
		i++;
	}
	printf("\n\n");
}

void	PRINT_lst_pipe(t_pipe *lst_pipe)
{
	t_pipe	*copy_lst;

	if (!lst_pipe)
	{
		printf("NULL: lst_pipe\n");
		return ;
	}
	copy_lst = lst_pipe;
	while (copy_lst)
	{
		printf("lst pipe: ");
		PRINT_lst_line(copy_lst->lst_line);
		printf("\nNEXT!!!\n");
		copy_lst = copy_lst->next;
	}
}

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
//	char  	*exp;

	if (ac != 1)
		print_error_exit(NULL, ERR_AC);
	(void)(av);
	msh = mshnew(ev);
	if (!msh)
		print_error_exit(NULL, ERR_MALLOC);
	while (1)
	{
		msh->read_line = readline("Minishell-> ");
		//exp = expand (msh->read_line, msh);
		//printf("%s\n", exp);
		if (!msh->read_line)
			print_error_exit(&msh, ERR_MALLOC);
		if (!ft_strncmp(msh->read_line, "exit", 4) && \
			ft_strlen(msh->read_line) == 4 )
			break ;//muy warning: esto tendremos que hacer en los executings (execve, etc...)		
		//printf("las comillas son %i, la primera comilla esta en %i\n\n", is_quotes_pair(msh->read_line, 0, -1), where_next_any_quote_is(msh->read_line, 0));
		if (check_ifempty_str(msh->read_line) == 0)
			add_history(msh->read_line);

		//comentado pero hay que descomentar despues (eliminar /* */)
 		if (is_quotes_pair(msh->read_line, 0, -1) != -1)
		{
			if (check_pipe_in_word(msh->read_line))
				msh->lst_pipe = new_lst_pipe(msh);
			else
				msh->lst_line = new_lst_line(msh, msh->read_line);
		}
		else
			print_warning(ERR_QUOTE); 

		//addstr_to_lst_line(msh->read_line, &msh->lst_line);//NECESITA MAS TEST, con este ejemplo funciona bien
	
		printf("\n");
		
		PRINT_lst_line(msh->lst_line);//para printear
		PRINT_lst_pipe(msh->lst_pipe);//para printear
		//free_str(&msh->read_line);
		free_lst_line(&msh->lst_line);
		free_lst_pipe(&msh->lst_pipe);
	}
	free_msh(&msh);
	return (0);
}
