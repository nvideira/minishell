/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:45:00 by jlebre            #+#    #+#             */
/*   Updated: 2023/01/03 20:48:22 by nvideira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser(char *input, char **env)
{
	char		**tmp;
	char		*tmp2;
	char		*tmp3;
	int			here;
	int			pipe_no;

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
	if (ft_strlen(input))
	 	add_history(input);
	if (check_quotes(input))
	{
		write(1, "minishell: syntax error: unclosed quotes\n", 41);
		return ;
	}
	pipe_no = count_pipes(input);
	com_info()->pipe_no = pipe_no;
	tmp = ft_split(input, '|');
	while (pipe_no >= 0)
	{
		lst_add_front(&com_info()->commands, add_mat_node(tmp[pipe_no]));
		pipe_no--;
	}
	free_matrix(tmp);
	if (com_info()->pipe_no > 0)
		init_pipes();
	process_input(env);
	// while (com_info()->commands)
	// {
	// 	print_matrix(com_info()->commands->arg);
	// 	com_info()->commands = com_info()->commands->next;
	// }
}
