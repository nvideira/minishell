/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:31 by jlebre            #+#    #+#             */
/*   Updated: 2022/10/25 15:59:31 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Função para aceder a uma struct em qualquer ponto do código com com_info()
t_command	*com_info(void)
{
	static t_command	a;

	return (&a);
}

// Main
// Inicia o shell e fica em loop para ler os comandos
// Se o comando for nulo (ctrl + D) ele sai do shell
// Se o comando for vazio (enter) ele ignora e volta para o loop
// Se o comando for valido ele chama o parser e process_input
int	main(int argc, char **argv, char **env)
{
	char		*input;

	(void)argc;
	(void)argv;
	init_shell(env);
	while (1)
	{
		catch_signal();
		input = readline(print_info());
		if (!input)
		{
			rl_clear_history();
			free (input);
			exit(com_info()->exit_value);
		}
		parser(input);
		process_input(env);
	}
	free (input);
	return (com_info()->exit_value);
}
