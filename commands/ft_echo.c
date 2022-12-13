/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:31:01 by marvin            #+#    #+#             */
/*   Updated: 2022/11/17 23:31:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Se não tiveres " " e tiveres mais de 1 argumento tem de imprimir todos

void	print_vars2(char **input)
{
	t_env_lst	*temp;
	char 		*name;

	name = input[1];
	temp = com_info()->env_lst;
	name++;
	while (temp)
	{
		if (!ft_strncmp(ft_strjoin(name, "="), temp->name, ft_strlen(name) - 1))
		{
			printf("%s\n", temp->value);
			return ;
		}
		temp = temp->next;
	}
}

void	print_vars(char **input)
{
	t_env_lst	*temp;
	char 		*name;

	name = input[1];
	temp = com_info()->vars;
	name++;
	while (temp)
	{
		if (!ft_strncmp(ft_strjoin(name, "="),temp->name, ft_strlen(name) - 1))
		{
			printf("%s\n", temp->value);
			return ;
		}
		temp = temp->next;
	}
	print_vars2(input);
}

void	ft_echo(char **input)
{
	int	i;

	if (!ft_strncmp(input[1], "$?", 3))
		printf("%d\n", com_info()->exit_value);
	else if (input[1][0] == '$' && ft_strlen(input[1]) < 2)
		printf("Error: no such file \"%s\"\n", input[1]);
	else if (input[1][0] == '$')
		print_vars(input);
	else if (!ft_strncmp(input[1], "-n", 3))
	{
		printf("%s%%\n\a", input[2]);
		com_info()->exit_value = 0;
	}
	else
	{
		i = 1;
		while (i < com_info()->nb_args)
		{
			printf("%s", input[i]);
			if ((com_info()->nb_args - i) != 1)
				printf(" ");
			i++;
		}
		printf("\n");
		com_info()->exit_value = 0;
	}
}


/*
INPUT: echo a b c
a b c

INPUT: echo "a" "b" "c"
a b c

INPUT: echo a\nb\nc
anbnc

INPUT: echo a \n b \n c
a n b n c

INPUT: echo "a\nb\nc"
a
b
c
*/