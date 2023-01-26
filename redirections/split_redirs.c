/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 01:57:54 by marvin            #+#    #+#             */
/*   Updated: 2023/01/26 01:57:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	Tem de se criar uma função no parser para confirmar se os redir
//	estão rodeados por espaços! Para o input vir "ls > a.txt" em vez de 
//	"ls>a.txt"

//	O split está feito a contar que as coisas vêm bem separadas

// Função para fazer o split dos redirecionamentos
// Faz a primeira alocação de memória para a matriz
char ***split_redir(char **input)
{
	char	***new;
	int		matlen;

	if (!input)
		return (NULL);
	matlen = ft_matmeasures(input);
	//printf("Total Len: %i\n\n", matlen);
	new = (char ***)malloc(sizeof(char **) * (matlen + 1));
	if (!new)
		return (NULL);
	split_all(input, new, matlen);
	new[matlen] = NULL;
	return (new);
}

// Faz a segunda alocação de memória para a matriz
int	split_all(char **input, char ***new, int matlen)
{
	int		i;
	int		j;
	int		nb_words;
	//int		test;

	i = 0;
	j = 0;
	while (j < matlen)
	{
		//test = 0;
		nb_words = count_second_word(input, i);
		//printf("Len[%i]: %i\n", j, nb_words);
		new[j] = malloc(sizeof(char *) * (nb_words + 1));
		if (!new[j])
			return (0);
		//printf("i: %i\n", i);
		fill_word(input, i, nb_words, new[j]);
		//while (test < nb_words)
		//{
			//printf("new[%i][%i]: %s\n", j, test, new[j][test]);
			//test++;
		//}
		i += nb_words;
		j++;
		//printf("\n");
	}
	new[matlen] = NULL;
	return (0);
}

// Preenche a matriz com as palavras
void	fill_word(char **input, int i, int nb_words, char **new)
{
	int j;

	j = 0;
	while (j < nb_words)
	{
		new[j] = ft_strdup(input[i]);
		if (!new[j])
			return ;
		j++;
		i++;
	}
	new[j] = NULL;
}

/*
int	split_all(char **input, int start, char ***new)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (input[i])
	{
		// while (input[i][j] && !ft_strchr(set, input[i][j]))
		// 	j++;
		while (input[i][j])
		{
			if (input[i][j] == 34)
				j = find_quotes(input[i], j, 34);
			if (input[i][j] == 39)
				j = find_quotes(input[i], j, 39);
			if (input[i][j] == '\0')
				break ;
		}
	}
	return (0);
}
*/