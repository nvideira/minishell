/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:15:16 by jlebre            #+#    #+#             */
/*   Updated: 2023/02/08 04:26:24 by marvin           ###   ########.fr       */
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

char	*ft_main(va_list arg, char *c)
{
	char	*error;
	char	*begin;
	char	*middle;
	char	*end;
	int		i;
	
	i = 0;
	error = NULL;
	while (c[i])
	{
		if (c[i] == '%')
		{
			begin = ft_substr(c, 0, i);
			end = ft_substr(c, i + 2, ft_strlen(c));
			i++;
			if (ft_strchr("cs", c[i]))
			{
				middle = check(c[i], arg);
				error = ft_strjoin(begin, middle);
				error = ft_strjoin(error, end);
			}
			else
				return (error);
		};
		i++;
	}
	return (error);
}

void	ft_error(char *err, ...)
{
	va_list	arg;
	char	*error;

	if (!err)
		return ;
	va_start(arg, err);
	error = ft_main(arg, (char *)err);
	va_end(arg);
	error = ft_strjoin("\033[0;31m", error),
	error = ft_strjoin(error, "\033[0m");
	perror(error);
	//free(error);
}
