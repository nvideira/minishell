/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:17:14 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/23 16:27:57 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_name_export(char *str, int len)
{
	char	*name;
	int		i;

	i = 0;
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		return (NULL);
	while (i < len)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_name_change_export(char *str, int len)
{
	char	*name;
	int		i;

	i = 0;
	name = malloc(sizeof(char) * (len + 2));
	if (!name)
		return (NULL);
	while (i < len && str[i])
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '=';
	i++;
	name[i] = '\0';
	return (name);
}

char	*get_value_export(char *str, int len)
{
	char	*value;
	int		len_val;
	int		i;

	i = 0;
	len_val = (ft_strlen(str) - (len + 1));
	value = malloc(sizeof(char) * (len_val + 1));
	if (!value)
		return (NULL);
	while (str[len])
	{
		value[i] = str[len];
		i++;
		len++;
	}
	value[i] = '\0';
	return (value);
}
