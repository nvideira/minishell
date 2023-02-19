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

char	*join_args(char **args)
{
	char	*input;
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	while (args[i])
	{
		input = ft_strjoin(tmp, args[i]);
		free(tmp);
		if (args[i + 1])
		{
			tmp = ft_strjoin(input, " ");
			free(input);
			input = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	return (input);
}

// Processa o $.
// Se for $? retorna o exit value.
// Se input[i][0] for $ e tiver mais que 1 char e tiver apenas 1 $,
// altera o valor com a funcao change_val.
// Se tiver 1 ou mais $ altera o valor com a funcao change_val2.

// >> 8 & 255
char	*check_ds(char *input)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split(input, ' ');
	while (args[i])
	{
		if (!ft_strncmp(args[i], "$?", 3))
			args[i] = ft_itoa((com_info()->exit_value >> 8 & 255));
		else if (args[i][0] == '$' && ft_strlen(args[i]) > 1
			&& count_ds(args[i]) == 1)
			args[i] = ft_strdup(change_val(args[i]));
		else if (count_ds(args[i]) >= 1 && (ft_strlen(args[i]) > 1))
			args[i] = change_val2(args[i], 0, 0);
		i++;
	}
	input = join_args(args);
	free_matrix(args);
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
