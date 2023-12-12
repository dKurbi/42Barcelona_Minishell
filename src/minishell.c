/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkurcbar <dkurcbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:05:38 by dkurcbar          #+#    #+#             */
/*   Updated: 2023/12/12 13:49:54 by dkurcbar         ###   ########.fr       */
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
    char* input;

    // Inicializar la biblioteca GNU Readline
    rl_bind_key('\t', rl_insert); // Habilitar el autocompletado con Tab

    while (1) {
        input = readline("Ingrese un comando: ");

        // Agregar la línea al historial
        add_history(input);

        if (input && *input) {
            printf("Comando ingresado: %s\n", input);
        }

        free(input);
    }

    return 0;
}
/* 
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

 	str = readline("");
	rl_replace_line("",0);
	printf("%i\n", i);
	return (0);*/

