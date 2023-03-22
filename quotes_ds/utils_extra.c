/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:56:27 by nvideira          #+#    #+#             */
/*   Updated: 2023/03/22 18:02:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_all_char(char **input)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			count++;
			j++;
		}
		i++;
	}
	return (count + i);
}

char	*join_args(char **args)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	new = malloc(sizeof(char) * count_all_char(args));
	if (!new)
		return (NULL);
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			new[k] = args[i][j];
			j++;
			k++;
		}
		if (args[i + 1])
			new[k++] = ' ';
		i++;
	}
	new[k] = '\0';
	return (new);
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
	char		*tmp;

	while (input[i])
	{
		if (input[i] == '\'')
			i = (skip_quotes_ds(input, i, '\''));
		if (input[i] == '$' && is_valid(input[i + 1]))
		{
			tmp = change_val2_help(input, i, j);
			free(input);
			input = ft_strdup(tmp);
			free(tmp);
			i = 0;
			j = 0;
		}
		else
			i++;
	}
	return (input);
}

char	*change_val2_help(char *input, int i, int j)
{
	char	*name;
	char	*tmp;

	while (is_valid(input[++i]))
		j++;
	name = ft_substr(input, (i - j - 1), (j + 1));
	if (cds(name, com_info()->env_lst) || cds(name, com_info()->vars))
		tmp = create_new(input, i, j, name);
	else
		tmp = remove_ds(input, ft_strlen(name));
	free(name);
	return (tmp);
}
