/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 02:37:02 by marvin            #+#    #+#             */
/*   Updated: 2023/01/26 02:37:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ECHO
void					print_vars(char **input);
void					print_vars2(char **input);

void	print_vars2(char **input)
{
	t_env_lst	*temp;
	char		*name;

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
	char		*name;

	name = input[1];
	temp = com_info()->vars;
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
	print_vars2(input);
}

// EXPORT
int	check_if_exists2(char *str)
{
	t_env_lst	*temp;
	char		*name;
	int			len;

	if (!str)
		return (0);
	len = 0;
	temp = com_info()->vars;
	while (str[len] != '=')
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

void	change_value2(char *str)
{
	t_env_lst	*head;
	char		*name;
	char		*value;
	int			len;

	len = 0;
	head = com_info()->vars;
	while (str[len] != '=')
		len++;
	name = get_name_change_export(str, len);
	value = get_value_export(str, len + 1);
	while (com_info()->vars->name != name)
	{
		if (!ft_strncmp(name, com_info()->vars->name, (len + 1)))
		{
			com_info()->vars->value = value;
			break ;
		}
		com_info()->vars = com_info()->vars->next;
	}
	com_info()->vars = head;
}

// PROCESS INPUT
int						check_if_exists_vars(char *str);
void					change_value_vars(char *str);

int	check_if_exists_vars(char *str)
{
	t_env_lst	*temp;
	char		*name;

	temp = com_info()->vars;
	name = get_name(str);
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(name)))
		{
			free(name);
			return (1);
		}
		temp = temp->next;
	}
	free(name);
	return (0);
}

void	change_value_vars(char *str)
{
	t_env_lst	*head;
	char		*name;
	char		*value;
	int			len;

	len = 0;
	head = com_info()->vars;
	while (str[len] != '=')
		len++;
	name = get_name_change_export(str, len);
	value = get_value_export(str, len);
	while (com_info()->vars->name != name)
	{
		if (!ft_strncmp(name, com_info()->vars->name, (len + 1)))
		{
			com_info()->vars->value = value;
			break ;
		}
		com_info()->vars = com_info()->vars->next;
	}
	com_info()->vars = head;
}