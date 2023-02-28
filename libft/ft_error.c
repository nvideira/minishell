/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:15:16 by jlebre            #+#    #+#             */
/*   Updated: 2023/02/28 18:05:01 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Guardar tudo numa str
// Mandar para o perror

#include "minishell.h"

char	*check(char c, va_list arg)
{
	if (c == 'c')
		return (ft_putchar_fde(va_arg(arg, int)));
	else if (c == 's')
		return (ft_putstr_fde(va_arg(arg, char *)));
	else
		return (NULL);
}

char	*get_error(char *begin, char *middle, char *end)
{
	char	*error;
	char	*temp;

	temp = ft_strjoin(begin, middle);
	error = ft_strjoin(temp, end);
	free_all(begin, end);
	free_all(temp, middle);
	return (error);
}

char	*ft_main(va_list arg, char *c)
{
	char	*error;
	char	*begin;
	char	*end;
	int		i;

	i = -1;
	error = NULL;
	begin = NULL;
	end = NULL;
	while (c[++i])
	{
		if (c[i] == '%')
		{
			begin = ft_substr(c, 0, i);
			end = ft_substr(c, i + 2, ft_strlen(c));
			if (ft_strchr("cs", c[++i]))
			{
				error = get_error(begin, check(c[i], arg), end);
			}
			else
			{
				free_all(begin, end);
				return (error);
			}
		}
	}
	return (error);
}

void	ft_error(char *err, ...)
{
	va_list	arg;
	char	*error;
	char	*temp;

	if (!err)
		return ;
	va_start(arg, err);
	error = ft_main(arg, (char *)err);
	va_end(arg);
	temp = ft_strjoin("\033[0;31m", error);
	free(error);
	error = ft_strjoin(temp, "\033[0m\n");
	write(2, error, ft_strlen(error));
	free_all(temp, error);
}
