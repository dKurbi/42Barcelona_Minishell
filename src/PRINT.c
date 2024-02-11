#include "../inc/minishell.h"

void	PRINT_lst_line(t_line *lst_line)
{
	if (!lst_line)
	{
		printf("LOL lst line nullllll\n");
		return ;
	}
	t_line *copy = lst_line;
	while (copy != NULL)
	{
		printf("LSTLINE LOOP: str - %s\n", copy->str);
		printf("LSTLINE LOOP: type - %d\n", copy->type);
		copy = copy->next;
	}
}