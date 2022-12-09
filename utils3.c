/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 16:18:52 by nvideira          #+#    #+#             */
/*   Updated: 2022/12/09 18:29:03 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strljoin(char const *s1, char const *s2, unsigned int len)
{
	char			*ns;
	unsigned int	i;
	unsigned int	j;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_substr(s2, 0, len));
	ns = malloc((ft_strlen(s1) + len) * sizeof(char) + 1);
	if (!ns)
		return (NULL);
	i = -1;
	while (s1[++i])
		ns[i] = s1[i];
	j = -1;
	while (s2[++j] && j < len)
		ns[i + j] = s2[j];
	ns[i + j] = '\0';
	return (ns);
}

void	lst_add_front(t_args **lst, t_args *new)
{
	if (*lst != NULL)
		new->next = *lst;
	*lst = new;
}