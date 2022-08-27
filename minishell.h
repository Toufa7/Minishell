/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:39:43 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 11:15:27 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define GREEN "\033[32m"
# define RESET "\033[0m"
# define PATH_MAX  4096
# define SING_QUOTES 39
# define DOUBLES_QUOTES 34
# define BACKSLASH 92
# define TAAB 9
# define SPAACE 32
# define TRUE 1 
# define FALSE 0 
# define AMBIGUOUS 0
# define INFILE 1
# define OUTFILE 2
# define APPENDFILE 3

typedef int	bool;

typedef struct s_tokens
{
	char	*token;
	char	*type;
	char	*cmp_red_in;
	char	*cmp_h_doc;
	char	*cmp_red_out;
	char	*cmp_append;
	size_t	red_in;
	size_t	red_out;
	size_t	here_do;
	size_t	app;
	size_t	redirections;
	size_t	delimiter;
	size_t	cmd;
	size_t	env_var;
	size_t	option;
	size_t	total;
}	t_tokens;

/*
	s_redirections types:
	0: ambiguous redirect
	1: in file
	2: out file
	3: append file
*/

typedef struct s_redirections
{
	char	*path;
	int		type;
}	t_redirections;

typedef struct s_global_data
{
	int		errno_cp;
	int		in_fd;
	int		out_fd;
	int		size;
	int		cmd_pipe_fds[2];
	int		pre_pipe_infd;
	char	**envp;
	bool	parse_error;
	pid_t	last_child_id;
	bool	is_in_herdoc;
	bool	redirection_error;
}	t_global_data;

typedef struct s_pipe_data
{
	char			*command;
	char			*cmd_path;
	char			**delimiter;
	char			**argv;
	bool			out_fd_set;
	bool			in_fd_set;
	bool			is_herdoc;
	t_redirections	**redirections;
}	t_pipe_data;

typedef struct s_parse
{
	char		*line;
	char		**splt_pipes;
	char		*orginal_string;
	char		*formated_input;
	char		*line_double_quotes;
	char		*no_splt;
	char		pipe;
	char		space;
	t_pipe_data	**pipe_data;
	t_tokens	*tokens;
}	t_parse;

// ----------- Parsing --------------------------

char		**pipes(char	*str);
char		*s_d_quotes(char *str);
char		*handling_quotes(char *str, char replaced_1, char replace_by);
char		*input_formating(char	*str);
char		*getting_back_original_input(char *str);
char		*get_env_variables(char *target, bool flag);
char		*get_env_in_herdoc(char *target);
void		initializer(t_tokens	*tokens);
void		input_analyse(t_tokens	*tokens);
void		token_and_type(t_parse *parse);
void		input_counter(t_tokens	*counter, t_tokens	*tokens);
t_tokens	*spliting_with_spaces(char	*str);
t_pipe_data	*get_pipe_data(t_parse	*parse);
bool		check_parse_errors(t_parse *parse);

// ----------- Execution -------------------------

void		mcd(char *path);
void		mpwd(void);
void		menv(char **argv, char *prefix, bool is_export);
void		mecho(char **argv);
void		mexit(char **argv);
void		munset(char **argv);
void		mexport(char **argv);
void		validate_cmd(t_pipe_data *pipe_data);
void		pipe_files_prep(t_pipe_data *pipe_data, bool is_builtin);
void		execution(t_pipe_data **pipe_data);
char		*get_cmd_path(char	*cmd, char	**exec_programs_dirs);
int			check_builtin(t_pipe_data *pipe_data);
void		exec_builtin(int builtin_nb, t_pipe_data *pipe_data);

// ----------- Shared Functions ------------------

void		ft_close(int n, int s);
void		free_str(void	*ptr); 
void		free_arr(void **arr);

void		parent_sigint(int sig);
void		herdoc_sigint(int sig);
void 		void_sig(int sig);
// void		child_sigquit(int sig);
// void		child_sigint(int sig);

void		*ft_calloc(size_t count, size_t size);
void		env_dup(char **env);
char		*ft_itoa(int n);
char		*get_var_val(int var_index);
char		**ft_realloc(char **dist, char *str);
char		*get_next_line(int fd);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
void		ft_putstr_fd(char *s, int fd);
void		ft_strncpy(char *dest, char *src, int n);
char		**ft_split(char const *s, char c);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			validate_var_name(char *var);
int			get_var_index(char *var);
int			ft_atoi(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);

t_global_data global_data;

#endif
