/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebre <jlebre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:59:44 by jlebre            #+#    #+#             */
/*   Updated: 2022/10/25 15:59:44 by jlebre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
/////////////////////////////////////////////////
# include <signal.h>
/////////////////////////////////////////////////
# include <sys/types.h>
# include <sys/wait.h>
/////////////////////////////////////////////////
# include <dirent.h>
/////////////////////////////////////////////////
# include <readline/readline.h>
# include <readline/history.h>
/////////////////////////////////////////////////


typedef struct s_command
{
	int					fd[2];
	pid_t				pid;
	int					status;
	char				*cmd;
	char 				*path;
	char				**args;
}   t_command;

typedef struct s_env_lst
{
	char				*name;
	char				*value;
	struct s_env_lst	*next;
}	t_env_lst;

//INIT SHELL
void					init_shell(char **env);

void					recieve();

//ENV_TO_LIST
void					lst_add_back(t_env_lst **lst, t_env_lst *new);
t_env_lst				*env_to_lst(char **env);
t_env_lst				*new_node(char *env);
t_env_lst				*ft_lstlast(t_env_lst *lst);
//FREE ENV
void					free_env(t_env_lst **env);

/*
//SOUND
void					play_sound(char **env, char *sound);
*/

//PRINT DIR
char					*print_info(void);
char					*print_dir(void);
void					print_header(char **env);
int						get_col(char **env);
int						get_lines(char **env);

//PROCESS INPUT
void					process_input(char *input, char **env);

//COMMANDS
void					commands(char **input, char **env);
void					env_commands(char **input, char **env);
char					*find_path(char *cmd, char **env);
void					change_dir(char **input);

//FT_ERROR
void					ft_error(char *err, char **env);

//SHELL_SPLIT_UTILS
int						find_quotes(const char *str, int i, int type);
void					*freematrix(char **ns, int msize);

//UTILS_PIPE
int						ft_strichr(const char *s, int start, int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*join_strings(char *path, int j, char *cmd);
char					*ft_substring(char const *s, unsigned int start, size_t len);


//UTILS
char					*ft_strjoin(char const *s1, char const *s2);
int						ft_strlen(const char *str);
char					*ft_substr(char const *s, unsigned int start, size_t len);
char					*ft_strdup(const char *s1);
void					*ft_memmove(void *dst, const void *src, size_t len);

//UTILS2
char					**ft_split(const char *s, char c);
int						ft_strcmp(char *s1, char *s2);
int 					strict_cmp(char *s1, char *s2);
void					ft_clear(void);
int						ft_strchr(const char *s, int c);
int						ft_atoi(const char *str);


//NORMAL COLORS
int						black(char *str);
int						red(char *str);
int						green(char *str);
int						yellow(char *str);
int						blue(char *str);
int						purple(char *str);
int						cyan(char *str);
int						white(char *str);

//BOLD
int						bold_black(char *str);
int						bold_red(char *str);
int						bold_green(char *str);
int						bold_yellow(char *str);
int						bold_blue(char *str);
int						bold_purple(char *str);
int						bold_cyan(char *str);
int						bold_white(char *str);

#endif