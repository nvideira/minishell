/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:22:23 by marvin            #+#    #+#             */
/*   Updated: 2023/01/11 14:22:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putchar_fde(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putstr_fde(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (write(fd, "(null)", 6));
	while (s[i])
	{
		ft_putchar_fde(s[i], fd);
		i++;
	}
	return (ft_strlen(s));
}

int	ft_putnbr_fde(int n, int k, int fd)
{
	if (n == (-2147483648))
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		ft_putchar_fde('-', fd);
		k++;
		n = -n;
	}
	k++;
	if (n > 9)
	{
		k = ft_putnbr_fde(n / 10, k, fd);
		n %= 10;
	}
	ft_putchar_fde(n + '0', fd);
	return (k);
}
