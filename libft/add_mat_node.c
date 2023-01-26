/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_mat_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:13:35 by marvin            #+#    #+#             */
/*   Updated: 2023/01/25 18:32:10 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*add_mat_node(char *args)
{
	t_args	*new_node;

	new_node = malloc(sizeof(t_args));
	if (!new_node)
		return (NULL);
	new_node->arg = ft_split(args, ' ');
	//new_node->redir_type = com_info()->redir_database[i];
	new_node->next = NULL;
	return (new_node);
}
