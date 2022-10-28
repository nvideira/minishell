/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:44:55 by jlebre            #+#    #+#             */
/*   Updated: 2022/10/26 17:47:17 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  play_sound(char **env, char *sound)
{
	//char	cwd[1024];
	char	*arr[3];
	int		cenas;

	cenas = fork();
	arr[0] = strdup("/bin/paplay");
	arr[1] =  strdup(sound);
	arr[2] = 0;
   
	if (!cenas)
		if (execve(arr[0], arr, env) == -1)
		{
			play_sound(env, "error.ogg");
			printf("ERROR!\n");
		}
	else
	  wait(0);
}
