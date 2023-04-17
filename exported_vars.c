/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exported_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:57:07 by marvin            #+#    #+#             */
/*   Updated: 2023/03/23 22:20:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Se o primeiro caracter for igual a '=':
// Erro

// Enquanto input[i] for diferente de NULL:
// Se input[i] tiver um '=':
// Chama a função exported_vars_utils
// Se não:
// Sai do ciclo
void	exported_vars(char **input)
{
	int	i;

	i = 0;
	if (input[0][i] == '=')
	{
		ft_error("%s not found\n", input[1]);
		return ;
	}
	while (input[i])
	{
		if (ft_strchr(input[i], '='))
			exported_vars_utils(input[i]);
		else
			break ;
		i++;
	}
	return ;
}

// Se já existir a variável no exported, mas não existir na lista de variáveis:
// Altera o valor no exported e adiciona à lista de variáveis

// Se já existir a variável na lista de variáveis:
// Altera o valor na lista de variáveis

// Se não existir a variável em lado nenhum:
// Adiciona à lista de variáveis
void	exported_vars_utils(char *input)
{
	if (check_if_exists(input, com_info()->env_lst)
		&& !check_if_exists(input, com_info()->vars))
	{
		change_value(input, com_info()->env_lst);
		lst_add_back(&com_info()->vars, new_node(input));
	}
	else if (check_if_exists(input, com_info()->vars))
		change_value(input, com_info()->vars);
	else
		lst_add_back(&com_info()->vars, new_node(input));
}

// Find Equal Sign
int	find_es(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

// Função que retorna o nome da variável
char	*get_name(char *str)
{
	int		len;
	int		i;
	char	*name;

	len = 0;
	i = 0;
	while (str[len] != '=')
		len++;
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		return (0);
	while (i < len)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}
