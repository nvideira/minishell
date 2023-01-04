/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:34:43 by marvin            #+#    #+#             */
/*   Updated: 2022/12/15 18:34:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	do_print(char **input, int start, int type)
{
	while (start < com_info()->commands->nb_args)
	{
		printf("%s", input[start]);
		if ((com_info()->commands->nb_args - start) != 1 && ft_strncmp(com_info()->commands->arg[start], "", 1)
			&& ft_strncmp(com_info()->commands->arg[start + 1], "", 1))
			printf(" ");
		start++;
	}
	if (type != 2)
		printf("\n");
	com_info()->exit_value = 0;
}

void	check_flag(char c)
{
	if (c == 'a')
		printf("\a");
	else if (c == 'b')
		printf("\b");
	else if (c == 't')
		printf("\t");
	else if (c == 'n')
		printf("\n");
	else if (c == 'v')
		printf("\v");
	else if (c == 'f')
		printf("\f");
	else if (c == 'r')
		printf("\r");
	return ;
}

void	process_flags(char **input, int start)
{
	int	i;

	i = 0;
	while (start < com_info()->commands->nb_args)
	{
		while (input[start][i])
		{
			if (input[start][i] == '\\')
			{
				i++;
				if (ft_strchr("abtnvfr", input[start][i]))
					check_flag(input[start][i]);
			}
			else
				printf("%c", input[start][i]);
			i++;
		}
		if ((com_info()->commands->nb_args - start) != 1)
			printf(" ");
		start++;
	}
	printf("\n");
	com_info()->exit_value = 0;
}
