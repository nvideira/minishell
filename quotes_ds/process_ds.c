/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:23:13 by marvin            #+#    #+#             */
/*   Updated: 2023/01/04 00:23:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Processa o $.
// Se for $? retorna o exit value.
// Se input[i][0] for $ e tiver mais que 1 char e tiver apenas 1 $,
// altera o valor com a funcao change_val.
// Se tiver 1 ou mais $ altera o valor com a funcao change_val2.
char	**check_ds(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_strncmp(input[i], "$?", 3))
			input[i] = ft_itoa(com_info()->exit_value);
		else if (input[i][0] == '$' && ft_strlen(input[i]) > 1
			&& count_ds(input[i]) == 1)
			input[i] = ft_strdup(change_val(input[i]));
		else if (count_ds(input[i]) >= 1 && (ft_strlen(input[i]) > 1))
			input[i] = change_val2(input[i], 0, 0);
		i++;
	}
	return (input);
}

// Altera o valor da variavel quando tiver apenas 1 $.
char	*change_val(char *input)
{
	t_env_lst	*temp;
	t_env_lst	*temp2;
	char		*name;

	name = input;
	temp = com_info()->vars;
	name++;
	while (temp)
	{
		if (!ft_strncmp(ft_strjoin(name, "="), temp->name, ft_strlen(name) + 1))
			return (temp->value);
		temp = temp->next;
	}
	temp2 = com_info()->env_lst;
	while (temp2)
	{
		if (!ft_strncmp(ft_strjoin(name, "=")
				, temp2->name, ft_strlen(name) + 1))
			return (temp2->value);
		temp2 = temp2->next;
	}
	return ("");
}

// Salta as aspas simples.
int	skip_quotes_ds(char *input, int i, char c)
{
	i++;
	while (input[i] && input[i] != c)
		i++;
	return (i);
}

// Altera o valor da variavel quando tiver um ou mais $.
// Se tiver só 1 $, é porque está no meio da string.
char	*change_val2(char *input, int i, int j)
{
	char		*name;

	while (input[i])
	{
		if (input[i] == '\'')
			i = skip_quotes_ds(input, i, '\'');
		if (input[i] == '$')
		{
			while (is_valid(input[++i]))
				j++;
			name = ft_substr(input, (i - j - 1), (j + 1));
			if (cds(name, com_info()->env_lst) || cds(name, com_info()->vars))
				input = create_new(input, i, j, name);
			else
				input = remove_ds(input, ft_strlen(name));
			i = 0;
			j = 0;
		}
		else
			i++;
	}
	return (input);
}

// Conta o numero de $ na string
int	count_ds(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}
