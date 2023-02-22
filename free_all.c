/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:35:18 by jlebre            #+#    #+#             */
/*   Updated: 2023/02/22 16:37:40 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_env_lst *lst)
{
	while (lst)
	{
		free(lst->name);
		free(lst->value);
		lst = lst->next;
	}
	free(lst);
}

void	my_free(char *ptr)
{
	if (*ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}