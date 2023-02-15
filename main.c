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
	char	*input;
	char	*info;

	(void)argc;
	(void)argv;
	init_shell(env);
	catch_signal();
	while (1)
	{
		info = print_info();
		input = readline(info);
		if (!input)
		{
			write(2, "exit\n", 5);
			rl_clear_history();
			free (input);
			free(info);
			exit(com_info()->exit_value >> 8 & 0xFF);
		}
		signal_block();
		parser(input, env);
		free(input);
		free(info);
		catch_signal();
	}
	return (com_info()->exit_value);
}
