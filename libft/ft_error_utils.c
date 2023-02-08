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

char	*ft_putchar_fde(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_putstr_fde(char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
char	*ft_putnbr_fde(int n, int k)
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
*/
