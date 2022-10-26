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
# include <string.h>
# include <unistd.h>

# include <sys/types.h>
# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

# define clear() printf("\033c")

//INIT SHELL
void		init_shell(char **env);

//SOUND
void		play_sound(char **env, char *sound);

//MAIN
int         main(int ac, char **av, char **env);

//PRINT DIR
char		*print_dir(void);

//TAKE INPUT
char		*take_input(void);

//PROCESS INPUT
void		process_input(char *input);

//UTILS
char        *ft_strjoin(char const *s1, char const *s2);
int         ft_strlen(const char *str);
char        *ft_substr(char const *s, unsigned int start, size_t len);
char        *ft_strdup(const char *s1);
void	    *ft_memmove(void *dst, const void *src, size_t len);

//UTILS 2

//SHELL_SPLIT
char        **ft_split(char const *s, char c);

//NORMAL COLORS
int			black(char *str);
int			red(char *str);
int			green(char *str);
int			yellow(char *str);
int			blue(char *str);
int			purple(char *str);
int			cyan(char *str);
int			white(char *str);

//BOLD
int			bold_black(char *str);
int			bold_red(char *str);
int			bold_green(char *str);
int			bold_yellow(char *str);
int			bold_blue(char *str);
int			bold_purple(char *str);
int			bold_cyan(char *str);
int			bold_white(char *str);

#endif