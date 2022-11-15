/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:27:14 by nvideira          #+#    #+#             */
/*   Updated: 2022/11/15 18:22:03 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_space(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}
int	heredoc(char *limiter)
{
	char	*here;
	int		file;

	file = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file < 0)
		perror("here_doc");
	while (1)
	{
		write(1, "heredoc> ", 9);
		here = get_next_line(0);
		if (!ft_strncmp(here, limiter, find_space(limiter)))
			break ;
		write(file, here, ft_strlen(here));
		free(here);
	}
	free(here);
	close(file);
	file = open(".heredoc_tmp", O_RDONLY);
	if (file < 0)
	{
		unlink(".heredoc_tmp");
		perror("here_doc");
	}
	return (file);
}

int	find_redirections(char *input)
{
	int i;
	int redir_no;

	i = 0;
	redir_no = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			redir_no++;
		i++;
	}
	return (redir_no);
}

char	**shell_split(char *str)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	arr = malloc(sizeof(char *) * (ft_strlen(str) + 1));
	while (str[i])
	{
		while (str[i] && str[i] == 32)
			i++;
		if (str[i] == '"' || str[i] == '\'')
		{
			if (ft_strchr(str + i + 1, str[i]))
			{
				arr[j] = ft_substr(str, i + 1, ft_strchr(str + i + 1, str[i]));
				j++;
			}
			else
			{
				
			}
		}
	}
}

void parsing(char *str)
{
	int		i;
	int		j;
	int		st_point;
	int		infile;
	char	***mat_arr;

	i = 0;
	j = 0;
	st_point = 0;
	if (str[0] == '<' && str[1] == '<')
	{
		infile = heredoc(str + 2);
		free(str);
		read(infile, str, 999999);
		close(infile);
	}
	mat_arr = malloc(sizeof(char **) * (find_redirections(str) + 2));
	while (str[i])
	{
		while (str[i] && str[i] != '|' && str[i] != '>' && str[i] != '<')
			i++;
		if (str[i] == '\0')
		{
			mat_arr[j] = shell_split(ft_substr(str, st_point, i - st_point));
			j++;
			break ;
		}
		else if (str[i] == '|')
		{
			mat_arr[j] = shell_split(ft_substr(str, st_point, i - st_point));
			st_point = i + 1;
			j++;
		}
	}
	mat_arr[j] = NULL;
}
