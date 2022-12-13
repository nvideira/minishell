/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 02:24:07 by marvin            #+#    #+#             */
/*   Updated: 2022/12/13 02:24:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_color_help(void)
{
	printf("HELP:\n");
	printf("0: \033[1;30mBlack\033[0m\n");
	printf("1: \033[0;31mRed\033[0m\n");
	printf("2: \033[0;32mGreen\033[0m\n");
	printf("3: \033[0;33mYellow\033[0m\n");
	printf("4: \033[0;34mBlue\033[0m\n");
	printf("5: \033[0;35mPurple\033[0m\n");
	printf("6: \033[0;36mCyan\033[0m\n");
	printf("7: \033[0;37mWhite\033[0m\n\n");
	printf("To make the color bold, ");
	printf("add a third argument with the number \"1\"\n");
	printf("\nchange_color 2 1\n\n");
	printf("Changes prompt color to \033[0;32mBold Green\033[0m\n\n\n\n");
}

void	do_change(char **input, int bold)
{
	char	*b;
	char	*color;

	if (bold == 3)
	{
		if (ft_strlen(input[2]) != 1 || ft_atoi(input[1]) < 0
			|| ft_atoi(input[1]) > 7 || ft_atoi(input[2]) < 0
			|| ft_atoi(input[2]) > 1)
			red("Change_Color: Invalid arguments\n");	
		else
			b = "1";
	}
	else
		b = "0";
	color = ft_strjoin("\033[", b);
	color = ft_strjoin(color, ";3");
	color = ft_strjoin(color, input[1]);
	color = ft_strjoin(color, "m:");
	com_info()->color = color;
}

void	change_color(char	**input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	if (!input[1])
	{
		red("Change_Color: Not enough arguments\n");	
		red("Try \"change_color --help\" for help\n");
		return ;	
	}
	if (i > 3)
	{
		red("Change_Color: Too much arguments\n");	
		red("Try \"change_color --help\" for help\n");
		return ;	
	}
	if (!ft_strncmp(input[1], "--help", 6))
		change_color_help();
	else if (ft_isdigit(input[1]) && ft_strlen(input[1]) == 1)
		do_change(input, i);
	else
		red("Change_Color: Invalid arguments\n");	
}
