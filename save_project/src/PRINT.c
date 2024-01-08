//ELIMINAMOS ESTE FICHERO DESPUES! ESTO ES NUESTRO "VISUALIZER" DEBUGGER

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

void	PRINT_comillas(char *read_line)
{
	if (!read_line)
		return ;
	printf("las comillas son %i, la primera comilla esta en %i\n\n\n", is_quotes_pair(read_line, 0, -1), where_next_any_quote_is(read_line, 0));
}