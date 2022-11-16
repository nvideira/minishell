/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:02:50 by nvideira          #+#    #+#             */
/*   Updated: 2022/11/16 18:54:36 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	find_redirections(char *input)
{
	int i;
	int redir_no;

	i = 0;
	redir_no = 0;
	if (input[0] == '<' && input[1] == '<')
		i++;
	while (input[i] != '\0')
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			redir_no++;
			if (input[i] == '<' && input[i + 1] == '<')
				i++;
			else if (input[i] == '>' && input[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (redir_no);
}

char	*find_limiter(char *input, int start)
{
	int 	i;
	char	*limiter;

	i = start;
	while (input[i] && input[i] == ' ')
	{
		start++;	
		i++;
	}
	while (input[i] && input[i] != ' ')
		i++;
	limiter = ft_substr(input, start, i - start);
	return (limiter);
}
char	*heredoc(char *input)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	char	*limiter;

	limiter = find_limiter(input, 2);
	tmp3 = ft_substr(input, 2 + ft_strlen(limiter),
		ft_strlen(input) - 2 - ft_strlen(limiter));
	while (1)
	{
		write(1, "heredoc> ", 9);
		tmp = get_next_line(0);
		if (!ft_strncmp(tmp, limiter, ft_strlen(limiter)))
			break ;
		tmp2 = ft_strjoin(tmp4, tmp);
		free(tmp);
		free(tmp4);
		tmp4 = ft_strdup(tmp2);
		free(tmp2);
	}
	tmp2 = ft_strjoin(tmp4, tmp3);
	return (tmp2);
}

void	wait_for_quotes(char *input, char type)
{
	
}

void	search_quotes(char *input)
{
	int i;
	int quotes;
	int	d_quotes;
	
	i = 0;
	quotes = 0;
	d_quotes = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			quotes++;
		else if (input[i] == '\"')
			d_quotes++;
		i++;
	}
	i = 0;
	while (input[i] != '\'' && input[i] != '\"')
		i++;
	if ((input[i] == '\'' && quotes % 2 != 0) || (input[i] == '\"' && d_quotes % 2 != 0))
		wait_for_quotes(input, input[i]);
}

void	parser(char *input)
{
    int 	i;
	int		redir_no;
	char	*tmp;
	char	*limiter;

    i = 0;
	search_quotes(input);
	if (ft_strncmp(input, "<<", 2))
	{
		tmp = heredoc(input);
		free(input);
		input = ft_strdup(tmp);
		free(tmp);
	}
	redir_no = find_redir(input);
    while (input[i])
    {
        if ()
    }
   
}