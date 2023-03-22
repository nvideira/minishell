/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:07:27 by marvin            #+#    #+#             */
/*   Updated: 2023/02/11 18:07:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_output(char *input)
{
	int	fd;
	int	i;
	int	nb;

	i = 0;
	nb = count_char(input, '>');
	while (nb && input[i])
	{
		if (input[i] != '>')
			i++;
		else if (special_quote(input, i) == 0)
		{
			fd = get_output_fd(input, nb, i);
			if (fd <= 0)
				i = (fd * -1) + 1;
			else
				return (fd);
			nb--;
		}
		else
			i++;
	}
	if (fd != -1 || i == -1)
		ft_error("Redirection output error\n");
	return (fd);
}

int	get_output_fd(char *input, int nb, int count)
{
	int		fd;
	char	*filename;

	if (input[count + 1] == '>')
	{
		count++;
		filename = out_file(input, count + 1);
		fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0666);
	}
	else
	{	
		filename = out_file(input, count + 1);
		fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
	}
	if (nb == 1)
	{
		free(filename);
		return (fd);
	}
	free(filename);
	close(fd);
	return (count * -1);
}

char	*out_file(char *input, int count)
{
	char	*filename;
	int		i;

	i = 0;
	filename = malloc(sizeof(char) * (ft_strlen(input) + 1));
	while (input[count] && input[count] == ' ')
		count++;
	while (ft_str1chr("<> ", input[count]) == 0 && input[count])
	{
		filename[i] = input[count];
		i++;
		count++;
	}
	filename[i] = '\0';
	return (filename);
}
