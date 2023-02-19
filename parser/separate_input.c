/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:52:13 by marvin            #+#    #+#             */
/*   Updated: 2023/01/30 22:52:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_put_space_before(char *input, int i)
{
	char	*new;
	int		len;
	int		j;

	j = 0;
	len = ft_strlen(input);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	while (input[j] && (j < (i + 1)))
	{
		new[j] = input[j];
		j++;
	}
	new[j++] = ' ';
	i++;
	while (i < (len + 1))
	{
		new[j] = input[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*ft_put_space_after(char *input, int i)
{
	char	*new;
	int		len;
	int		j;

	j = 0;
	len = ft_strlen(input);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	while (input[j] && (j < i))
	{
		new[j] = input[j];
		j++;
	}
	new[j] = ' ';
	j++;
	while (i < (len + 1))
	{
		new[j] = input[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*separate_input(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<' || input[i] == '|')
		{
			if (input[i - 1] != ' ' && input[i - 1] != input[i])
				input = ft_put_space_before(input, i - 1);
			if (input[i + 1] && input[i + 1] != ' ' && input[i + 1] != input[i])
				input = ft_put_space_after(input, i + 1);
		}
		i++;
	}
	return (input);
}
