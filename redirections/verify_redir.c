/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:57:19 by marvin            #+#    #+#             */
/*   Updated: 2023/01/30 22:57:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify_redir_2(char *input)
{
	int	i;

	i = 0;
	printf("input: %s\n", input);
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] == '>' && (input[i + 2] == '>'
				|| input[i + 2] == '<' || input[i + 2] == '|'))
		{
			ft_error("minishell: syntax error near\
				unexpected token `newline'\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	verify_redir(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<' || input[i] == '|')
		{
			j = i + 1;
			while (input[j] && ft_space(input[j]))
				j++;
			if (input[j] != input[i] && (input[j] == '>'
					|| input[j] == '<' || input[j] == '|'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
