/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:18:35 by nvideira          #+#    #+#             */
/*   Updated: 2023/01/23 15:50:34 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env_lst **env)
{
	while ((*env)->next)
	{
		free((*env)->name);
		free((*env)->value);
		(*env)->name = NULL;
		(*env)->value = NULL;
		*env = (*env)->next;
	}
}
