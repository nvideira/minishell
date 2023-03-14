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

void	free_all(char *input, char *info)
{
	free(input);
	free(info);
}

void	ft_clean(char *input, char *info)
{
	write(2, "exit\n", 5);
	rl_clear_history();
	free_all(input, info);
	free_list(com_info()->env_lst);
	free_list(com_info()->vars);
	exit(com_info()->exit_value >> 8 & 0xFF);
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

	init_shell(argc, argv, env);
	catch_signal();
	while (1)
	{
		info = print_info();
		input = readline(info);
		if (!input)
			ft_clean(input, info);
		signal_block();
		input = parser(input, env);
		free(info);
		catch_signal();
	}
	rl_clear_history();
	if (input)
		free(input);
	return (com_info()->exit_value);
}
