/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:50 by nvideira          #+#    #+#             */
/*   Updated: 2022/10/26 17:11:02 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *find_command(char *input, int start)
{
    int i;
    char *command;

    i = start;
    while (input[i] != ' ' && input[i] != '\0')
        i++;
    command = ft_substr(input, start, i - start);
    return (command);
}

void	parser(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        find_command(input, i);
    }
   
}