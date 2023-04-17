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

char	*get_return_value(char **args, int i)
{
	char	*tmp;
	char	*before;
	char	*after;
	char	*new;
	int		j;

	j = 0;
	while (args[i][j])
	{
		if (args[i][j] == '$' && args[i][j + 1] == '?'
			&& !surround_quote(args[i], j, '\''))
		{
			before = ft_substr(args[i], 0, j);
			tmp = ft_itoa(convert_return_value(com_info()->exit_value));
			after = ft_substr(args[i], j + 2, ft_strlen(args[i]));
			new = ft_strjoin(before, tmp);
			free(args[i]);
			args[i] = ft_strjoin(new, after);
			free_all(before, after);
			free_all(tmp, new);
		}
		j++;
	}
	return (args[i]);
}

char	*check_ds_help(char **args, int i)
{
	char	*tmp;

	args[i] = get_return_value(args, i);
	if (args[i][0] == '$' && ft_strlen(args[i]) > 1
		&& count_ds(args[i]) == 1 && is_valid(args[i][1]))
	{
		tmp = change_val(args[i]);
		free(args[i]);
		args[i] = ft_strdup(tmp);
	}
	else if (count_ds(args[i]) >= 1 && (ft_strlen(args[i]) > 1))
	{
		tmp = change_val2(args[i], 0, 0);
		args[i] = ft_strdup(tmp);
	}
	free(tmp);
	return (args[i]);
}

// Processa o $.
// Se for $? retorna o exit value.
// Se input[i][0] for $ e tiver mais que 1 char e tiver apenas 1 $,
// altera o valor com a funcao change_val.
// Se tiver 1 ou mais $ altera o valor com a funcao change_val2.

// >> 8 & 255
char	*check_ds(char *input)
{
	char	**args;
	int		i;
	char	*new;

	i = 0;
	if (!ft_str1chr(input, '$'))
		return (input);
	args = ft_split(input, ' ');
	while (args[i])
	{
		args[i] = check_ds_help(args, i);
		i++;
	}
	new = join_args(args);
	free(input);
	free_matrix(args);
	return (new);
}

char	*change_val_help(char *name, t_env_lst *lst)
{
	t_env_lst	*temp;

	if (!name || !lst)
		return (NULL);
	temp = lst;
	while (temp)
	{
		if (!temp->name)
			return (NULL);
		if (!ft_strncmp(name, temp->name, ft_strlen(name)))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

// Altera o valor da variavel quando tiver apenas 1 $.
char	*change_val(char *input)
{
	char	*ret;
	char	*name;

	name = ft_strjoin(++input, "=");
	ret = change_val_help(name, com_info()->vars);
	if (ret)
	{
		free(name);
		return (ret);
	}
	ret = change_val_help(name, com_info()->env_lst);
	if (ret)
	{
		free(name);
		return (ret);
	}
	free(name);
	return ("");
}
