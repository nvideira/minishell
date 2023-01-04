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

// A função change_val2 serve para alterar o valor de $_ no meio de uma str

char	*change_val2(char *input)
{
	int			i;
	int			j;
	static char	*name;
	
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			while (input[i] != ' ')
			{
				name[j] = input[i];
				j++;
				i++;
			}
			//check name;
			//change;
			//join to previous str
		}
		i++;
	}
	
	return (input);
}

char	*change_val(char *input)
{
	t_env_lst	*temp;
	t_env_lst	*temp2;
	char 		*name;

	name = input;
	temp = com_info()->vars;
	name++;
	while (temp)
	{
		if (!ft_strncmp(ft_strjoin(name, "="), temp->name, ft_strlen(name) + 1))
			return (temp->value);
		temp = temp->next;
	}
	temp2 = com_info()->env_lst;
	while (temp2)
	{
		if (!ft_strncmp(ft_strjoin(name, "="), temp2->name, ft_strlen(name) + 1))
			return (temp2->value);
		temp2 = temp2->next;
	}
	return ("");
}

char	**check_ds(char **input)
{
	int	i;

	i = 1;
	if (!input[1])
		return (input);
	while (input[i])
	{
		if (!ft_strncmp(input[i], "$?", 3) && find_pelicula(input[i]) != 2)
			input[i] = ft_itoa(com_info()->exit_value);
		else if (input[i][0] == '$' && ft_strlen(input[i]) > 1)
			input[i] = ft_strdup(change_val(input[i]));
		else if (ft_strchr(input[i], '$') && ft_strlen(input[i]) > 1
			&& find_pelicula(input[i]) != 2)
			input[i] = ft_strdup(change_val2(input[i]));
		i++;
	}
	return (input);
}
