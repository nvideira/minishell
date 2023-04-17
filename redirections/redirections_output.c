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

int	get_fd(char *filename, int type)
{
	int	fd;

	if (type == 1)
		fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0666);
	else
		fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
	return (fd);
}

//if (check_file_existence(filename))
//	exit(1);
int	get_output_fd(char *input, int nb, int count)
{
	int		fd;
	char	*filename;
	int		type;

	type = 0;
	if (input[count + 1] == '>')
	{
		count++;
		type = 1;
	}
	filename = out_file(input, count + 1);
	if (check_file_access(filename, W_OK))
		exit(1);
	fd = get_fd(filename, type);
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
	while (input[count] && !ft_str1chr("<> ", input[count]))
	{
		filename[i] = input[count];
		i++;
		count++;
	}
	filename[i] = '\0';
	return (filename);
}
