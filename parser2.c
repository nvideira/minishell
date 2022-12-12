/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:55:59 by nvideira          #+#    #+#             */
/*   Updated: 2022/12/12 18:05:17 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*com_info(void)
{
	static t_command	a;

	return (&a);
}

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

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

char	*heredoc(char *limiter, int *here)
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
	*here = 1;
	return(ret_str);
}

char	*find_limiter(char *input, int start)
{
	int		i;
	char	*limiter;

	while (input[start] && (input[start] == ' ' || input[start] == '\t'))
		start++;
	i = start;
	while (input[i] && input[i] != ' ' && input[i] != '\t')
		i++;
	limiter = ft_substr(input, start, i - start);
	return (limiter);
}

// int	inside_quotes(char *string, int q_mod, int dq_mod)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (string[i] && string[i] != '\'' && string[i] != '\"')
// 		i++;
// 	if (!string[i])
// 		return (0);
// 	j = i + 1;
// 	while (string[j] && string[j] != string[i])
// 	{
// 		if (string[i] == '\'' && string[j] == '\"')
// 			dq_mod++;
// 		else if (string[i] == '\"' && string[j] == '\'')
// 			q_mod++;
// 		j++;
// 	}
// }

//void	norm_help(char *string, int j, int *quotes, int *dquotes)
//{
	// if (commands[i][j] == '\'' && dquotes == 0 && quotes == 0)
	// 	quotes = 1;
	// else if (commands[i][j] == '\'' && dquotes == 0 && quotes == 1)
	// 	quotes = 0;
	// else if (commands[i][j] == '\"' && dquotes == 0 && quotes == 0)
	// 	dquotes = 1;
	// else if (commands[i][j] == '\"' && dquotes == 1 && quotes == 0)
	// 	dquotes = 0;
//}

int	check_quotes(char *commands)
{
	int	i;
	int	quotes;
	int	dquotes;

	i = 0;
	quotes = 0;
	dquotes = 0;
	while (commands[i])
	{
		if (commands[i] == '\'' && dquotes == 0 && quotes == 0)
			quotes = 1;
		else if (commands[i] == '\'' && dquotes == 0 && quotes == 1)
			quotes = 0;
		else if (commands[i] == '\"' && dquotes == 0 && quotes == 0)
			dquotes = 1;
		else if (commands[i] == '\"' && dquotes == 1 && quotes == 0)
			dquotes = 0;
		i++;
	}
	if (quotes || dquotes)
		return (1);
	return (0);
}

char	***split_split(char **matrix)
{
	char	***ret;
	int		i;

	i = 0;
	while (matrix[i])
		i++;
	ret = malloc(sizeof(char **) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		ret[i] = ft_split(matrix[i], ' ');
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	skip_quotes(char *input, int i, char quote)
{
	int	j;

	j = ++i;
	while (input[j] && input[j] != quote)
		j++;
	if (!input[j])
		return (i);
	return (j);
}

int	count_pipes(char *input)
{
	int	i;
	int	pipe_no;

	i = 0;
	pipe_no = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_quotes(input, i, input[i]);
		else if (input[i] == '|')
			pipe_no++;
		i++;
	}
	return (pipe_no);
}

void	parser(char *input)
{
	char		**tmp;
	char		*tmp2;
	char		*tmp3;
	//int			i;
	int			here;
	int			pipe_no;
	
	//i = 0;
	here = 0;
	tmp2 = NULL;
	tmp3 = NULL;
	if (empty_prompt(input))
		return ;
	if (!ft_strncmp(input, "<<", 2))
		tmp2 = heredoc(find_limiter(input, 2), &here);
	if (tmp2)
	{
		tmp3 = ft_strjoin(input, tmp2);
		free(tmp2);
		free(input);
		input = ft_strdup(tmp3);
		free(tmp3);
	}
	// if (ft_strlen(input))
	// 	add_history(input);
	if (check_quotes(input))
	{
		write(1, "minishell: syntax error: unclosed quotes\n", 41);
		return ;
	}
	pipe_no = count_pipes(input);
	tmp = ft_split(input, '|');
	while (pipe_no >= 0)
	{
		printf("teste\n");
		lst_add_front(&com_info()->commands, add_mat_node(tmp[pipe_no]));
		pipe_no--;
	}
	free_matrix(tmp);	
	while (com_info()->commands)
	{
		print_matrix(com_info()->commands->arg);
		com_info()->commands = com_info()->commands->next;
	}
	
}


int main(int ac, char **av)
{
	//char	**parsed;

	(void)ac;
	if (ac < 2)
		return (0);
	parser(av[1]);
	// if (parsed)
	// 	print_matrix(parsed);
	return (0);
}