/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:56:17 by jlebre            #+#    #+#             */
/*   Updated: 2022/12/07 17:58:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Recria o comando cd
// Tem as funcionalidades de - e ~
// Também tem a funcionalidade de mudar o diretório atual
void	ft_cd(char **input, char **env)
{
	char	*curr;
	char	*new;

	if (!cd_errors(input))
		return ;
	curr = print_dir();
	new = ft_strjoin(curr, "/");
	if (input[1])
	{
		if (!ft_strncmp(input[1], "-", 2))
		{
			if (!check_if_exists("OLDPWD", com_info()->env_lst))
			{
				ft_error("minishell: cd: OLDPWD not set\n");
				return ;
			}
			do_cd(get_cenas_do_env("OLDPWD="), get_cenas_do_env("OLDPWD="), env);
		}
		else
			do_cd(input[1], ft_strjoin(new, input[1]), env);
	}
	else
		do_cd(get_cenas_do_env("HOME="), get_cenas_do_env("OLDPWD="), env);
	com_info()->exit_value = 0;
	change_pwd("OLDPWD=", curr, env);
}

// Função que muda o diretório atual
void	do_cd(char *new_dir, char *new_pwd, char **env)
{
	chdir(new_dir);
	change_pwd("PWD=", new_pwd, env);
}

// Função que vê se há erros no comando cd
int	cd_errors(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	if (i > 2)
	{
		ft_error("cd: string not in pwd: %s\n", input[1]);
		return (0);
	}
	if (i == 2)
	{
		if (ft_strlen(input[1]) == 1 && !ft_strncmp(input[1], "-", 2))
			return (1);
		if (i == 1)
			return (1);
		if (access(input[1], F_OK) != 0)
		{
			ft_error("cd: no such file or directory: %s\n", input[1]);
			return (0);
		}
	}
	return (1);
}

// FUnção que altera o PWD no env
void	change_pwd_env(char *type, int size, char *val, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (!ft_strncmp(type, env[i], size))
		{
			while (val[j])
			{
				env[i][j + size] = val[j];
				j++;
			}
			env[i][j + size] = '\0';
		}
		i++;
	}
}

// Função que altera o PWD na lista de variáveis de ambiente
void	change_pwd(char *type, char *str, char **env)
{
	t_env_lst	*head;
	char		*val;

	head = com_info()->env_lst;
	while (com_info()->env_lst)
	{
		if (!ft_strncmp(type, com_info()->env_lst->name, ft_strlen(type)))
		{
			val = ft_strdup(str);
			com_info()->env_lst->value = val;
			change_pwd_env(type, ft_strlen(type), val, env);
			break ;
		}
		com_info()->env_lst = com_info()->env_lst->next;
	}
	com_info()->env_lst = head;
}
