/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 04:25:07 by marvin            #+#    #+#             */
/*   Updated: 2023/01/12 04:25:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(char c)
{
	if (c == '\n' || c == '\v' || c == '\0'
		|| c == '\r' || c == '\t' || c == '\f' || c == '$'
		|| c == '\'')
		return (0);
	return (1);
}

char	*create_new(char *input, int i, int j, char *name)
{
	char	*new;
	char	*val;
	int		k;
	int		l;
	int		size;

	k = 0;
	l = 0;
	val = ft_strdup(change_val(name));
	size = ((ft_strlen(input) - j) + ft_strlen(val));
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (k < (i - j - 1))
	{
		new[k] = input[k];
		k++;
	}
	while (val[l])
		new[k++] = val[l++];
	while (k < size)
		new[k++] = input[i++];
	new[k] = '\0';
	free(val);
	return (new);
}

// Remove $
char	*remove_ds(char *input, int size)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(input) - size));
	if (!new)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$' && i < size)
		{
			i++;
			while (is_valid(input[i]) && input[i])
				i++;
			while (input[i])
				new[j++] = input[i++];
		}
		else
			new[j++] = input[i++];
	}
	new[j] = '\0';
	return (new);
}

// Check If Dollar Sign Exists
int	cds(char *input, t_env_lst *temp)
{
	char *name;

	input++;
	name = ft_strjoin(input, "=");
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(input)))
		{
			free(name);
			return (1);
		}
		temp = temp->next;
	}
	free(name);
	return (0);
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
