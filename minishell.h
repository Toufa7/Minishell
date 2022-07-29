/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:39:43 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/26 21:41:34 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:
	✅ char	*heredoc_limiter;
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

# define PATH_MAX  4096
# define SUCCESS	0
# define FAILURE	1
# define sing_quotes 39
# define doubles_quotes 34
typedef int bool;
# define TRUE 1
# define FALSE 0

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
	int		size;
	char	**command;
	char	**in_files;
	char	**delimiter;
	char	**out_files;
	char	**app_outfile;
	char	**options;
	char	**env_var;
	int		parse_error;
}	t_input;

typedef struct s_parse
{
	char		*line;
	char		**splt_pipes;
	char		*orginal_string;
	char		*formated_input;
	char		*line_double_quotes;
	t_input		*input;
	t_tokens	*tokens;
}	t_parse;

typedef struct s_pipe_data
{
	char	*infile_path;
	int		infile_status;
	char	*outfile_path;
	char	**cmds_names;
	char	**cmds_paths;
	int		cmds_size;
	int		is_heredoc;
	char	*heredoc_limiter;
	int		cmd_pipe_fds[2];
	int		here_doc_pipe_fds[2];
}	t_pipe_data;

// ----------- Parsing --------------------------

char		**pipes(char	*str);
char		*handling_quotes(char *str);
char		*input_formating(char	*str);
char		*getting_back_original_input(char *str);
char		*get_env_variables(char	*target);
void		input_types(t_parse	*parse);
void		initializer(t_tokens	*tokens);
void		input_analyse(t_tokens	*tokens);
void		input_counter(t_tokens	*counter, t_tokens	*tokens);
t_tokens	*spliting_with_spaces(char	*str);
int		stop_executing(t_parse *parse);
// ----------- Execution -------------------------

void    mcd(char *path);
void    mpwd(void);
void	menv();
void    mmecho(char **argv);
void    mexit(char **argv);
void	munset(char **argv);
void	mexport(char **argv);
void	execution(int argc, char *argv[], char *envp[]);
void	get_herdoc(t_pipe_data *pipe_data);
char	*get_cmd(char *str);
void	validate_cmd(char *cmd, char **cmd_path, char **exec_programs_dirs);
int		validate_infile(char *infile_path);
void	child_process(int i, int input_fd,
			t_pipe_data *pipe_data, char *envp[]);

// ----------- Shared Functions ------------------

void	free_str(char *str);
void	free_arr(char **arr);
int		validate_var_name(char *var);
char	**ft_realloc(char **input, char *str);
void	env_dup(char **env);
int		get_var_index(char *var, int n);
char	*get_next_line(int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_strncpy(char *dest, char *src, int n);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
void	free_str(char *str);
void	free_arr(char **arr);

#endif


// FOEIUWGHFEEUHOFUOIU