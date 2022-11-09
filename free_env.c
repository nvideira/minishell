/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:18:35 by nvideira          #+#    #+#             */
/*   Updated: 2022/11/09 17:28:33 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env_lst **env)
{
	while ((*env)->next)
	{
		free((*env)->name);
		free((*env)->value);
		free(env);
		*env = (*env)->next;
	}
}