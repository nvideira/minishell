/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:55:59 by nvideira          #+#    #+#             */
/*   Updated: 2022/12/06 15:55:43 by nvideira         ###   ########.fr       */
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

char	*find_limiter(char *input, int start)
{
	int		i;
	char	*limiter;

	i = start;
	while (input[i] && input[i] != ' ')
		i++;
	limiter = ft_substr(input, start, i - start);
	return (limiter);
}

int	inside_quotes(char *string, int q_mod, int dq_mod)
{
	int	i;
	int	j;

	i = 0;
	while (string[i] && string[i] != '\'' && string[i] != '\"')
		i++;
	if (!string[i])
		return (0);
	j = i + 1;
	while (string[j] && string[j] != string[i])
	{
		if (string[i] == '\'' && string[j] == '\"')
			dq_mod++;
		else if (string[i] == '\"' && string[j] == '\'')
			q_mod++;
		j++;
	}
}

void	norm_help(char *string, int j, int *quotes, int *dquotes)
{
	if (commands[i][j] == '\'' && dquotes == 0 && quotes == 0)
		quotes = 1;
	else if (commands[i][j] == '\'' && dquotes == 0 && quotes == 1)
		quotes = 0;
	else if (commands[i][j] == '\"' && dquotes == 0 && quotes == 0)
		dquotes = 1;
	else if (commands[i][j] == '\"' && dquotes == 1 && quotes == 0)
		dquotes = 0;
}

int	check_quotes(char **commands)
{
	int	i;
	int	j;
	int	quotes;
	int	dquotes;

	i = 0;
	quotes = 0;
	dquotes = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			norm_help(commands[i], j, &quotes, &dquotes);
			j++;
		}
		if (quotes || dquotes)
			return (1);
		i++;
	}
	return (0);
}

char	**parser(char *input)
{
	char		**tmp;
	int			i;
	
	i = 0;
	if (empty_prompt(input))
		return (NULL);
	if (ft_strlen(input))
		add_history(input);
	tmp = ft_split(input, ' ');
	if (check_quotes(tmp))
	{
		write(1, "minishell: syntax error: unclosed quotes\n", 41);
		return (NULL);
	}
	if (!ft_strncmp(tmp[i], "<<", 2))
	{
		if (input[2] != ' ')
			com_info()->args[0] = heredoc(find_limiter(input, 2));
		else
			com_info()->args[0] = heredoc(tmp[1]);
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