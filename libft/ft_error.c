/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:15:16 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/25 16:46:09 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Guardar tudo numa str
// Mandar para o perror

#include "minishell.h"

static int	check(char **c, va_list arg)
{
	if (**c == 'c')
		return (ft_putchar_fde(va_arg(arg, int), 2));
	else if (**c == 's')
		return (ft_putstr_fde(va_arg(arg, char *), 2));
	else if (**c == 'i')
		return (ft_putnbr_fde(va_arg(arg, int), 0, 2));
	else if (**c == '%')
		return (ft_putchar_fde(**c, 2));
	else
		return (1);
}

static int	ft_main(va_list arg, char *c)
{
	int	counter;

	counter = 0;
	while (*c)
	{
		if (*c == '%')
		{
			c++;
			if (ft_strchr("csi%", *c))
				counter += check(&c, arg);
			else
				return (counter);
		}
		else
			counter += write(1, c, 1);
		c++;
	}
	return (counter);
}

void	ft_error(char *err, ...)
{
	va_list	arg;

	if (!err)
		return ;
	va_start(arg, err);
	ft_main(arg, (char *)err);
	va_end(arg);
}
