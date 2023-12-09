/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassambe <iassambe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/09 17:12:08 by iassambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	int	i;

	i = 0;
	(void)ac;
	(void)av;
	(void)env;

	rl_bind_key('\t', rl_complete);

    // Leer una línea usando readline
    char *line = readline("Ingrese su línea: ");

    // Reemplazar la línea actual con una nueva línea
    rl_replace_line("Nueva línea reemplazada", 1);
	printf("%s\n", line);
    // Imprimir el prompt y el nuevo contenido de la línea
    rl_redisplay();
	printf("%s\n", line);
	rl_on_new_line ();
	printf("%s\n", line);
	rl_clear_history();
	printf("%s\n", line);
    // Liberar la memoria utilizada por la línea
    free(line);

/* 	str = readline("");
	rl_replace_line("",0);
	printf("%i\n", i);
	return (0);*/
} 
