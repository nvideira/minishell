/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:57:06 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/03 18:36:18 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	empty_prompt(char *input)
{
	int	i;

	i = 0;
	if (!input[i])
		return (1);
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*heredoc(char *limiter, int *here)
{
	char	*tmp;
	char	*tmp2;
	char	*ret_str;
	
	ret_str = NULL;
	while (1)
	{
		write(1, "heredoc> ", 9);
		tmp = get_next_line(0);
		if (!ft_strncmp(tmp, limiter, ft_strlen(limiter)))
			break ;
		if (ret_str)
		{
			tmp2 = ft_strjoin(ret_str, tmp);
			free(ret_str);
		}
		else
			tmp2 = ft_strdup(tmp);
		free(tmp);
		ret_str = ft_strdup(tmp2);
		free(tmp2);
	}
	free(tmp);
	*here = 1;
	return(ret_str);
}