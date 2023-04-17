/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exported.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:27:47 by marvin            #+#    #+#             */
/*   Updated: 2023/03/23 18:27:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_exported(char *name, char *value)
{
	char	*str;
	char	*temp;

	str = ft_strjoin("declare -x ", name);
	temp = ft_strjoin(str, "\"");
	free(str);
	str = ft_strjoin(temp, value);
	free(temp);
	temp = ft_strjoin(str, "\"\n");
	free(str);
	write(1, temp, ft_strlen(temp));
	free(temp);
}

void	write_exported2(char *name)
{
	char	*str;
	char	*temp;

	str = ft_strjoin("declare -x ", name);
	temp = ft_strjoin(str, "\n");
	free(str);
	write(1, temp, ft_strlen(temp));
	free(temp);
}

// Imprime as variaveis exportadas
void	print_exported(char **input)
{
	t_env_lst	*temp;
	char		*value;

	(void)input;
	temp = sort_list(com_info()->env_lst);
	while (temp)
	{
		if (ft_str1chr(temp->name, '='))
		{
			value = remove_quotes(temp->value, '"');
			free(temp->value);
			temp->value = ft_strdup(value);
			free(value);
			write_exported(temp->name, temp->value);
		}
		else if (!ft_str1chr(temp->name, '='))
			write_exported2(temp->name);
		temp = temp->next;
	}
	com_info()->exit_value = 0;
}
