/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:41:42 by nvideira          #+#    #+#             */
/*   Updated: 2023/01/22 23:05:26 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir_type(char *input, int j)
{
	if (input[j] == '>')
	{
		if (input[j + 1] == '>')
			return (1);
		else
			return (2);
	}
	else if (input[j] == '<')
	{
		if (input[j + 1] == '<')
			return (3);
		else
			return (4);
	}
	return (0);
}

void	redirections(char **input, int i, int j, int type)
{
	int		fd;
	char	*file;

	if (input[i + 1] && input[i + 1] == input[i])
		perror("minishell: syntax error near unexpected token");
	if (((type == 1 || type == 3) && input[i][j + 2] != '\0'))
		file = ft_substr(input[i], j + 2, ft_strlen(input[i]));
	else if ((type == 2 || type == 4) && input[i][j + 1] != '\0')
		file = ft_substr(input[i], j + 1, ft_strlen(input[i]));
	else
		file = ft_substr(input[i + 1], 0, ft_strlen(input[i + 1]));
	if (type == 1)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (type == 2)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == 4)
		fd = open(file, O_RDONLY);
	else if (type == 3)
		fd = heredoc(file);
	if (type == 1 || type == 2)
		dup2(fd, STDOUT_FILENO);
	else if (type == 4 || type == 3)
		dup2(fd, STDIN_FILENO);
	close(fd);
	free(file);
}

void	check_redir(char **input)
{
	int	i;
	int	j;
	int	type;

	i = 0;
	type = 0;
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (input[i][j] == '>' || input[i][j] == '<')
			{
				type = check_redir_type(input[i], j);
				redirections(input, i, j, type);
			}
			j++;
		}
		i++;
	}
}
