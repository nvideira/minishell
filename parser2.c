/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:55:59 by nvideira          #+#    #+#             */
/*   Updated: 2022/11/29 19:24:32 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_prompt(char *input)
{
	int	i;

	i = 0;
	if (!input[i])
		return (1);
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*heredoc(char *limiter)
{
	char	*tmp;
	char	*tmp2;
	char	*ret_str;
	
	ret_str = NULL;
	while (1)
	{
		write(1, "heredoc> ", 9);
		tmp = get_next_line(0);
		if (!ft_strncmp(tmp, limiter, ft_strlen(limiter)))
			break ;
		if (ret_str)
		{
			tmp2 = ft_strjoin(ret_str, tmp);
			free(ret_str);
		}
		else
			tmp2 = ft_strdup(tmp);
		free(tmp);
		ret_str = ft_strdup(tmp2);
		free(tmp2);
	}
	free(tmp);
	return(ret_str);
}

char	**parser(char *input)
{
	t_command	*command;
	char		**tmp;
	int			i;
	
	i = 0;
	if (empty_prompt(input))
		return (NULL);
	tmp = ft_split(input, ' ');
	if (!ft_strncmp(tmp[i], "<<", 2))
	{
		command->args[0] = heredoc(tmp[1]);
	}
}

int main(int ac, char **av)
{
	char	**parsed;

	(void)ac;
	if (ac < 2)
		return (0);
	parsed = parser(av[1]);
	if (parsed)
		print_matrix(parsed);
	return (0);
}