/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:44:55 by jlebre            #+#    #+#             */
/*   Updated: 2022/11/07 18:56:30 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  play_sound(char **env, char *sound)
{
	char	*arr[3];
	int		cenas;

	arr[0] = ft_strdup("/bin/paplay");
	arr[1] = ft_strdup(sound);
	arr[2] = 0;
	cenas = fork();
	if (!cenas)
	{	
		if (execve(arr[0], arr, env) == -1)
		{
			play_sound(env, "error.ogg");
			printf("ERROR!\n");
		}
	}
	else
	  wait(0);
	free(arr[0]);
	free(arr[1]);
}
