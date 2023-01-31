/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:59:57 by marvin            #+#    #+#             */
/*   Updated: 2023/01/26 01:59:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Conta o número de char** que serão alocadas na matriz
int	ft_matmeasures(char **input)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 1;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (input[i][j] == '>' || input[i][j] == '<')
			{
				if (input[i][j + 1] == '>' || input[i][j + 1] == '<')
					j++;
				count += 2;
			}
			j++;
		}
		i++;
	}
	return (count);
}

// Conta o número de palavras que serão alocadas na matriz
int	count_second_word(char **input, int i)
{
	int	count;

	count = 0;
	if (input[i][0] == '>' || input[i][0] == '<')
		return (1);
	while (input[i] && input[i][0] != '>' && input[i][0] != '<')
	{
		count++;
		i++;
	}
	return (count);
}

// Verifica se o char está contido no set
int	ft_strstr(char *str, char *set)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// Retorna o tamanho da string até o próximo redirect
int	get_size(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '>' && input[i] != '<')
		i++;
	return (i);
}

// Imprime a matriz
void	print_matrix_redir(char ***matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			printf("matrix[%i][%i]: %s\n", i, j, matrix[i][j]);
			j++;
		}
		i++;
	}
}
