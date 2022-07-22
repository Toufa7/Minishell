/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:39:43 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/22 16:18:07 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:
	char	*heredoc_limiter;
*/


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define GREEN "\033[32m"
# define RESET "\033[0m"
# define TRUE 1
# define FALSE 0
# define PATH_MAX  4096

typedef int bool;
#define true 1
#define false 0

char	**genv;

typedef struct s_tokens
{
	char	*token;
	char	*type;
	size_t	red_in;
	size_t	red_out;
	size_t	here_do;
	size_t	app;
	size_t	in_file;
	size_t	out_file;
	size_t	doc_file;
	size_t	app_file;
	size_t	cmd;
}	t_tokens;

typedef struct s_input
{
	char	**in_files;
	char	**out_files;
	char	**app_outfile;
	char	**delimiter;
	char	**command;
}	t_input;

typedef struct s_parse
{
	char		*line;
	char		*formated_input;
	char		**splt_pipes;
	t_tokens	*tokens;
	t_input		*input;
}	t_parse;

// ----------- Parsing --------------------------

char		*get_env_variables(char	**env, char	*target);
char		**pipes(char	*str);
char		*input_formating(char	*str);
void		input_analyse(t_tokens	*tokens);
t_tokens	*spliting_with_spaces(char	*str);
void		input_counter(t_tokens	*counter, t_tokens	*tokens);
void		initializer(t_tokens	*tokens);
void		input_types(t_parse	*parse);

// ----------- Execution -------------------------

void    cd(char *path);
void    pwd(void);
void	env();
void    echo(char **argv);
void    mexit(char **argv);

// ----------- Shared Functions ------------------

void	env_dup(char **env);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
#endif