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
	char	*tmp;
	char	*new;

	i = 0;
	if (!ft_strchr(input, '$'))
		return (input);
	args = ft_split(input, ' ');
	while (args[i])
	{
		if (!ft_strncmp(args[i], "$?", 3))
		{
			tmp = ft_itoa((com_info()->exit_value >> 8 & 255));
			free(args[i]);
			args[i] = ft_strdup(tmp);
			free(tmp);
		}
		else if (args[i][0] == '$' && ft_strlen(args[i]) > 1
			&& count_ds(args[i]) == 1)
		{
			tmp = change_val(args[i]);
			free(args[i]);
			args[i] = ft_strdup(tmp);
			//free(tmp);
		}
		else if (count_ds(args[i]) >= 1 && (ft_strlen(args[i]) > 1))
		{
			tmp = change_val2(args[i], 0, 0);
			//free(args[i]);
			args[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	new = join_args(args);
	free(input);
	free_matrix(args);
	return (new);
}

// Altera o valor da variavel quando tiver apenas 1 $.
char	*change_val(char *input)
{
	t_env_lst	*temp;
	t_env_lst	*temp2;
	char		*name;

	input++;
	name = ft_strjoin(input, "=");
	temp = com_info()->vars;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(name)))
		{
			free(name);
			return (temp->value);
		}
		temp = temp->next;
	}
	temp2 = com_info()->env_lst;
	while (temp2)
	{
		if (!ft_strncmp(name
				, temp2->name, ft_strlen(name)))
		{
			free(name);
			return (temp2->value);
		}
		temp2 = temp2->next;
	}
	free(name);
	return (ft_strdup(""));
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
	char		*tmp;

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
				tmp = create_new(input, i, j, name);
			else
				tmp = remove_ds(input, ft_strlen(name));
			free(input);
			input = ft_strdup(tmp);
			free(tmp);
			free(name);
			i = 0;
			j = 0;
		}
		else
			i++;
	}
	return (input);
}
