/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:08:14 by marvin            #+#    #+#             */
/*   Updated: 2023/02/15 13:13:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(char *input)
{
	int	fd;
	int	i;
	int	nb;

	i = 0;
	fd = -1;
	nb = count_char(input, '<');
	while (nb && input[i])
	{
		if (input[i] != '<')
			i++;
		else
		{
			if (nb == 1)
				fd = get_input_fd(input, nb, i);
			else
				i = get_input_fd(input, nb, i);
			if (i < 0)
				break ;
			nb--;
		}
	}
	if (fd != -1 || i == -1)
		ft_error("Redirection input error\n");
	return (fd);
}

int	get_input_fd(char *input, int nb, int count)
{
	char	*filename;
	int		fd;

	if (input[count + 1] == '<')
	{
		filename = out_file(input, count + 2);
		fd = heredoc(filename);
		nb = 1;
	}
	else
	{
		filename = out_file(input, count + 1);
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			count = -1;
	}
	if (nb == 1)
	{
		free(filename);
		return (fd);
	}
	free(filename);
	close(fd);
	return (count + 1);
}

char	*in_file(char *input, int count)
{
	int		i;
	char	*filename;

	i = 0;
	while (input[count] && input[count] != ' ' && input[count] != '<')
	{
		i++;
		count++;
	}
	filename = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (input[count] && input[count] != ' ' && input[count] != '<')
	{
		filename[i] = input[count];
		i++;
		count++;
	}
	filename[i] = '\0';
	return (filename);
}
