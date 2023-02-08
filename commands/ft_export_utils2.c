/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:40:48 by marvin            #+#    #+#             */
/*   Updated: 2022/12/28 00:40:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Verifica se a variável já existe na lista de variáveis de ambiente
// e na lista de variáveis locais

// Se existir na env_lst e na vars_lst, altera o valor da variável nas duas
// Se não existir na env_lst, mas existir na vars_lst,
// altera o valor da variável na vars_lst e adiciona a variável na env_lst
void	check_export(char *input)
{
	int	exist1;
	int	exist2;

	exist1 = check_if_exists(input, com_info()->env_lst);
	exist2 = check_if_exists(input, com_info()->vars);
	if (exist1)
	{
		if (exist2)
			change_value(input, com_info()->vars);
		change_value(input, com_info()->env_lst);
	}
	else if (!exist1)
	{
		if (exist2)
			change_value(input, com_info()->vars);
		lst_add_back(&com_info()->env_lst, new_node(input));
	}
}

// Verifica se a variável já existe na lista passada como argumento
int	check_if_exists(char *str, t_env_lst *lst)
{
	t_env_lst	*temp;
	char		*name;
	int			len;

	if (!str)
		return (0);
	len = 0;
	temp = lst;
	while (str[len] && str[len] != '=' && str[len] != '\0')
		len++;
	name = get_name_export(str, len);
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, len))
		{
			free(name);
			return (1);
		}
		temp = temp->next;
	}
	free(name);
	return (0);
}

// Altera o valor da variável na lista passada como argumento
void	change_value(char *str, t_env_lst *lst)
{
	t_env_lst	*head;
	char		*name;
	char		*value;
	int			len;

	len = 0;
	head = lst;
	while (str[len] && str[len] != '=' && str[len] != '\0')
		len++;
	name = get_name_change_export(str, len);
	value = get_value_export(str, len + 1);
	while (lst->name != ft_substr(name, 0, len))
	{
		if (!ft_strncmp(ft_substr(name, 0, len), lst->name, (len)))
		{
			if (!ft_strchr(lst->name, '='))
				lst->name = ft_strdup(name);
			lst->value = ft_strdup(value);
			break ;
		}
		lst = lst->next;
	}
	lst = head;
	free(name);
	free(value);
}
