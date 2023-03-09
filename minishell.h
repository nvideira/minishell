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
# include <fcntl.h>
//
# include <signal.h>
//
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
//
# include <dirent.h>
//
# include <readline/readline.h>
# include <readline/history.h>
// PIPEX
# include <fcntl.h>
# include <errno.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/*___ _____ ___ _   _  ___ _____ ___ 
 / __|_   _| _ \ | | |/ __|_   _/ __|
 \__ \ | | |   / |_| | (__  | | \__ \
 |___/ |_| |_|_\\___/ \___| |_| |___/*/
typedef struct s_env_lst
{
	char				*name;
	char				*value;
	struct s_env_lst	*next;
	struct s_env_lst	*prev;
}	t_env_lst;

typedef struct s_args
{
	char				**arg;
	int					nb_args;
	int					redir_type;
	struct s_args		*next;
}	t_args;

typedef struct s_command
{
	pid_t				*pid;
	int					fd[2];
	int					pipe_fd;
	int					exit_value;
	t_env_lst			*env_lst;
	t_env_lst			*vars;
	int					nb_args;
	char				*color;
	char				**env;
}	t_command;

/*__  __ ___ _  _ ___ ___ _  _ ___ _    _    
 |  \/  |_ _| \| |_ _/ __| || | __| |  | |   
 | |\/| || || .` || |\__ \ __ | _|| |__| |__ 
 |_|  |_|___|_|\_|___|___/_||_|___|____|____|*/
t_command				*com_info(void);
void					free_list(t_env_lst *lst);
void					free_all(char *input, char *info);
void					my_free(char *input);	

//INIT SHELL
void					init_shell(int argc, char **argv, char **env);
char					*gce(char *str);

//SIGNALS
void					catch_signal(void);
void					signal_block(void);

//PRINT DIR
char					*print_info(void);
char					*print_dir(void);

/*___ _  ___   __
 | __| \| \ \ / /
 | _|| .` |\ V / 
 |___|_|\_| \_/*/
//ENV_TO_LIST
t_env_lst				*env_to_lst(char **env);
t_env_lst				*new_node(char *env);
t_env_lst				*ft_lstlast(t_env_lst *lst);
void					lst_add_back(t_env_lst **lst, t_env_lst *new);

//FREE ENV
void					free_env(t_env_lst **env);

/*___  _   ___  ___ ___ ___ 
 | _ \/_\ | _ \/ __| __| _ \
 |  _/ _ \|   /\__ \ _||   /
 |_|/_/ \_\_|_\|___/___|_|_\*/
//PARSER
char 					*parser(char *input, char **env);
int						skip_quotes(char *input, int i, char quote);
char					***split_split(char **matrix);
int						check_quotes(char *commands);
int						empty_prompt(char *input);
void					print_matrix(char **matrix);
void					free_matrix(char **matrix);

//PARSER CHECKS
int 					parser_checks(char *input);
int						parser_checks2(char *input);
int						check_xor(char *input);
int						check_and(char *input);
int						find_quote_position(char *input, char type);
int						check_if_inside_quotes(char *input, int i);

//PARSE INPUT
char					*parse_input(char *input);
char					*parse_input2(char *input);
char					**parse_input3(char **input);
char					*separate_input(char *input);
char					**parse_cenas(char **arg);
int     				is_space(char c);
char					*put_spaces(char *input);
int						count_words(char *input);

//PROCESS INPUT
char *process_input(char **args, char *input, char **env);
int 					ft_find_char(char *str, char c);
int						ft_find_in_matrix(char **matrix, char c);
int						count_args(char **matrix);
int						check_special(char *input, char c);
int						special_quote(char *input, int i);
int						ft_str1chr(const char *s, int c);

//EXPORTED VARS
void					exported_vars(char **input);
void					exported_vars_utils(char *input);
int						find_es(char *str);
int						cds(char *input, t_env_lst *temp);
char					*remove_ds(char *input, int size);
char					*create_new(char *input, int i, int j, char *name);
int						is_valid(char c);
int						count_ds(char *str);

//QUOTES
char 					*process_quotes(char *input);
char 					*process_peliculas(char *input);
int						find_quote(char *str);
int						find_pelicula(char *str);
char					*remove_quotes(char *input, char quote);
//char					*remove_peliculas(char *input);
int						surround_quote(char *input, int index, int quote);

//DOLLAR SIGN
char					*check_ds(char *input);
char					*change_val(char *input);
char					*change_val2(char *input, int i, int j);

/*___ ___ ___ ___ ___ 
 | _ \_ _| _ \ __/ __|
 |  _/| ||  _/ _|\__ \
 |_| |___|_| |___|___/*/
void					execute_pipe(char **input, int count, char **env);
void					pipe_commands(char **input, char **env);
void					child_input(char **input, int count);
void					ft_wait_pid(int counter);

/*___ ___ ___ ___ ___ 
 | _ \ __|   \_ _| _ \
 |   / _|| |) | ||   /
 |_|_\___|___/___|_|_\*/
void					redirections(char *input, char **env);
char					*get_filename(char *input, int count);

//INPUT
int						redirect_input(char *input);
int						get_input_fd(char *input, int nb, int count);
char					*in_file(char *input, int count);

//OUTPUT
int						redirect_output(char *input);
int						get_output_fd(char *input, int nb, int count);
char					*out_file(char *input, int count);
int						count_char(char *input, char c);
int						check_redir_type(char *input);
int						heredoc(char *limiter);
int						verify_redir(char *input);
int						verify_redir_2(char *input);
int						check_file_access(char *file);

/* ___ ___  __  __ __  __   _   _  _ ___  ___ 
  / __/ _ \|  \/  |  \/  | /_\ | \| |   \/ __|
 | (_| (_) | |\/| | |\/| |/ _ \| .` | |) \__ \
  \___\___/|_|  |_|_|  |_/_/ \_\_|\_|___/|___/
*/
void					commands(char *input, char **env, int is_fork);
void					commands2(char **arg, char **env, int is_fork);
int						parent_commands(char *input, char **env);
void					fork_commands(char **input, char **env, int is_fork);

//DEFAULT COMMANDS
void					env_commands(char **input, char **env);
char					*find_path(char *cmd, t_env_lst *env_lst);
char					*find_return_path(char *path, int j, char *cmd);

//CHANGE COLOR
void					change_color(char	**input);
void					do_change(char **input, int bold);
void					change_color_help(void);

//CD
void					ft_cd(char **input, char **env);
void					do_cd(char *new_dir, char *new_pwd, char **env);
void					change_pwd(char *type, char *str, char **env);
int						cd_errors(char **input);
void					change_pwd_env(char *type, int size,
							char *val, char **env);

//ECHO
void					ft_echo(char **input);
void					do_print(char **input, int start, int type);
void					check_flag(char c);
void					process_flags(char **input, int start);

//ENV
void					ft_env(char **input);

//EXIT
void					ft_exit(char **input);
void					check_error_3(char *arg, char **input);
char					*print_vars_exit(char **input);
void					do_exit(int exit_value, char **input);
void					exit_errors(int error, char **input);
int						check_size_int(char *str);

//EXPORT
void					*ft_export(char **input);
void					change_value(char *str, t_env_lst *lst);
int						check_if_exists(char *str, t_env_lst *lst);
void					print_exported(char **input);
void					check_export(char *input);
t_env_lst				*sort_list(t_env_lst *curr);
char					*get_name_export(char *str, int len);
char					*get_name_change_export(char *str, int len);
char					*get_value_export(char *str, int len);

//PWD
void					ft_pwd(void);
int						ft_isdigit(char *str);

//UNSET
void					ft_unset(char **input);
void					unset_error(void);
void					do_unset(char *input, t_env_lst *lst);
int						check_if_exists_unset(char *input, t_env_lst *temp);
void					check_unset(char *input);

/*_   _ _____ ___ _    ___ 
 | | | |_   _|_ _| |  / __|
 | |_| | | |  | || |__\__ \
  \___/  |_| |___|____|___/*/
//FT_ERROR
void					ft_error(char *err, ...);
char					*ft_putchar_fde(char c);
char					*ft_putstr_fde(char *s);
char					*ft_putnbr_fde(int n, int k);

char					*ft_strtrim(char const *s1, char const *set);

//ITOA
char					*ft_itoa(int number);
int						size_of_number(long nb);

//SHELL_SPLIT_UTILS
int						ft_space(char s);
void					*freematrix(char **ns, int msize);
int						ft_ispipe(char s, char c);

//UTILS_PIPE
int						ft_strichr(const char *s, int start, int c);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*join_strings(char *path, int j, char *cmd);
char					*ft_substring(char const *s, unsigned int start,
							size_t len);

//UTILS
char					*ft_strjoin(char const *s1, char const *s2);
int						ft_strlen(const char *str);
char					*ft_strdup(const char *s1);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					ft_putstr_fd(char *s, int fd);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);

//UTILS2
char					**ft_split(const char *s, char c);
int						find_quotes(const char *str, int i, int type);
int						ft_strcmp(char *s1, char *s2);
int						strict_cmp(char *s1, char *s2);
void					ft_clear(void);
int						ft_strchr(const char *s, int c);
int						ft_atoi(const char *str);

//UTILS3
void					lst_add_front(t_args **lst, t_args *new);
t_args					*add_mat_node(char *args);
char					*ft_strljoin(char const *s1, char const *s2,
							unsigned int len);

//GET_NEXT_LINE
char					*get_next_line(int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putchar_fd(char c, int fd);

#endif
