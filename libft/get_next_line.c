/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:19:10 by jlebre            #+#    #+#             */
/*   Updated: 2023/03/21 16:45:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_leftover(char **storage)
{
	char	*return_of_the_string;
	int		i;
	char	*intern;

	i = 0;
	while ((*storage)[i] != '\n' && (*storage)[i] != '\0')
		i++;
	return_of_the_string = ft_substr(*storage, 0, i + 1);
	intern = NULL;
	if ((*storage)[i] == '\n' && (*storage)[i + 1] != '\0')
	{
		intern = ft_substr(*storage, i + 1, ft_strlen(*storage) - i);
		free(*storage);
		*storage = ft_strdup(intern);
		free(intern);
		intern = NULL;
	}
	else
	{
		free(*storage);
		*storage = NULL;
	}
	return (return_of_the_string);
}

static char	*update_stored(char **storage, char *string)
{
	int		i;
	char	*return_of_the_string;
	char	*intern;

	i = 0;
	while ((*storage)[i] != '\n' && (*storage)[i] != '\0')
		i++;
	intern = ft_strljoin(string, *storage, i + 1);
	free(string);
	return_of_the_string = ft_strdup(intern);
	free(intern);
	if ((*storage)[i] == '\n' && (*storage)[i + 1] != '\0')
	{
		intern = ft_substr(*storage, i + 1, ft_strlen(*storage) - i);
		free(*storage);
		*storage = ft_strdup(intern);
		free(intern);
		intern = NULL;
	}
	else
	{
		free(*storage);
		*storage = NULL;
	}
	return (return_of_the_string);
}

static char	*reading(int fd, char **storage)
{
	char		*temp;
	char		buffer[BUFFER_SIZE + 1];
	int			chomp;

	chomp = read(fd, buffer, BUFFER_SIZE);
	if (chomp <= 0)
	{
		if (*storage != NULL)
			free(*storage);
		*storage = NULL;
		return (NULL);
	}
	buffer[chomp] = '\0';
	*storage = ft_strdup(buffer);
	while (chomp > 0 && !ft_strchr(buffer, '\n'))
	{
		chomp = read(fd, buffer, BUFFER_SIZE);
		buffer[chomp] = '\0';
		temp = ft_strljoin(*storage, buffer, ft_strlen(buffer));
		free(*storage);
		*storage = ft_strdup(temp);
		free(temp);
	}
	return (*storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*string;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	string = NULL;
	if (storage)
	{
		string = add_leftover(&storage);
		if (ft_strchr(string, '\n'))
			return (string);
	}
	storage = reading(fd, &storage);
	if (!storage && !string)
		return (NULL);
	if (storage)
		string = update_stored(&storage, string);
	return (string);
}
