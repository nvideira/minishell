/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:45:00 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/22 23:16:50 by nvideira         ###   ########.fr       */
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
	if (check_xor(input))
	{
		ft_error("minishell: syntax error near unexpected token `|'\n");
		return ;
	}
	parser3(input);
}

void	parser3(char *input)
{
	char		**tmp;
	int			pipe_no;
	
	pipe_no = count_pipes(input);
	com_info()->pipe_no = pipe_no;
	tmp = ft_split(input, '|');
	//com_info()->redir_no = count_redirs(tmp);
	while (pipe_no >= 0)
	{
		lst_add_front(&com_info()->commands, add_mat_node(tmp[pipe_no]));
		pipe_no--;
	}
	free_matrix(tmp);
	com_info()->commands->arg = parse_cenas(com_info()->commands->arg);
	if (com_info()->pipe_no > 0)
		init_pipes();
}
