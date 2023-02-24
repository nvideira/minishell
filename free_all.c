/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:35:18 by jlebre            #+#    #+#             */
/*   Updated: 2023/02/24 17:29:02 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_env_lst *lst)
{
	while (lst)
	{
		free(lst->name);
		lst->name = NULL;
		free(lst->value);
		lst->value = NULL;
		free(lst);
		lst = lst->next;
	}
	free(lst);
	lst = NULL;
}

void	my_free(char *ptr)
{
	if (*ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}