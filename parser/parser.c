/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:45:00 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/26 05:04:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**parse_cenas(char **arg)
{
	arg = process_quotes(arg);
	arg = check_ds(arg);
	arg = process_peliculas(arg);
	return (arg);
}

int	check_xor(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_and(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '&')
			return (1);
		i++;
	}
	return (0);
}

void	parser(char *input)
{
	char		*tmp2;
	char		*tmp3;

	tmp2 = NULL;
	tmp3 = NULL;
	if (empty_prompt(input))
		return ;
	if (tmp2)
	{
		tmp3 = ft_strjoin(input, tmp2);
		free(tmp2);
		free(input);
		input = ft_strdup(tmp3);
		free(tmp3);
	}
	if (ft_strlen(input))
	 	add_history(input);
	parser2(input);
}

void	parser2(char *input)
{
	if (check_quotes(input))
	{
		ft_error("minishell: syntax error: unclosed quotes\n");
		return ;
	}
	if (check_xor(input)) // Se a seguir a > estiver um |, dá o mesmo erro
	{
		ft_error("minishell: syntax error near unexpected token `|'\n");
		return ;
	}
	if (check_and(input))
	{
		ft_error("minishell: syntax error near unexpected token `&'\n");
		return ;
	}
	if (!verify_redir(input))
	{
		ft_error("minishell: syntax error near unexpected token `'\n");
		return ;
	}
	/*
	if () // Se a seguir a > estiver \n dá erro
	{
		ft_error("minishell: syntax error near unexpected token `newline'\n");
		return ;
	}
	*/
	parser3(input);
}

void	parser3(char *input)
{
	char		**tmp;
	int			pipe_no;
	int			i;
	
	i = 0;
	pipe_no = count_pipes(input);
	com_info()->pipe_no = pipe_no;
	tmp = ft_split(input, '|');
	while (pipe_no >= 0)
	{
		lst_add_front(&com_info()->commands, add_mat_node(tmp[pipe_no]));
		pipe_no--;
		i++;
	}
	free_matrix(tmp);
	com_info()->commands->arg = parse_cenas(com_info()->commands->arg);
	if (com_info()->pipe_no > 0)
		init_pipes();
}
