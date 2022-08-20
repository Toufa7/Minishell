/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:39:43 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/20 15:36:22 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TODO:
	✅ char	*heredoc_limiter;
	Adding array of s_input in ordre to deal with only arguments passsed to one pipe
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
# include <sys/types.h>
# include <sys/stat.h>

# define GREEN "\033[32m"
# define RESET "\033[0m"
# define PATH_MAX  4096
# define SING_QUOTES 39
# define DOUBLES_QUOTES 34
typedef int bool;
# define TRUE 1 
# define FALSE 0

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
	size_t	in_file;
	size_t	out_file;
	size_t	delimiter;
	size_t	app_file;
	size_t	cmd;
	size_t	env_var;
	size_t	option;
	size_t	total;
}	t_tokens;

typedef

typedef struct s_global_data
{
	char	**envp;
	char	*pwd_copy;
	int 	errno_cp;
	int 	in_fd;
	int 	out_fd;
	pid_t	last_child_id;
	bool	parse_error;
	bool	is_in_herdoc;
	int		size;
	int		cmd_pipe_fds[2];
	int		here_doc_pipe_fds[2];
	int		pre_pipe_infd;
}	t_global_data;

typedef struct s_pipe_data
{
	char	*command;
	char	*cmd_path;
	char	**in_files;
	char	**delimiter;
	char	**out_files;
	char	**app_outfile;
	char	**argv;
	bool	out_fd_set;
	bool	in_fd_set;
	bool	is_herdoc;
}	t_pipe_data;

typedef struct s_parse
{
	char		*line;
	char		**splt_pipes;
	char		*orginal_string;
	char		*formated_input;
	char		*line_double_quotes;
	char		*dont_splt;
	char		pipe;
	char		space;
	t_pipe_data	**pipe_data;
	t_tokens	*tokens;
}	t_parse;

// ----------- Parsing --------------------------

char		**pipes(char	*str);
char    	*remove_quotes(char *str, char removed);
char		*handling_quotes(char *str, char replaced_1, char replace_by);
char		*input_formating(char	*str);
char		*getting_back_original_input(char *str);
char		*get_env_variables(char *target);
char		*get_env_in_herdoc(char *target);
void		initializer(t_tokens	*tokens);
void		input_analyse(t_tokens	*tokens);
void		input_counter(t_tokens	*counter, t_tokens	*tokens);
t_tokens	*spliting_with_spaces(char	*str);
t_pipe_data	*get_pipe_data(t_parse	*parse);
bool		check_parse_errors(t_parse *parse);

// ----------- Execution -------------------------

void	mcd(char *path);
void    mpwd(void);
void	menv(char **argv, char *prefix, bool is_export);
void    mecho(char **argv);
void    mexit(char **argv);
void	munset(char **argv);
void	mexport(char **argv);
void	execution(t_pipe_data **pipe_data);
void	get_herdoc(t_pipe_data *pipe_data);
char	*get_cmd_path(char *cmd, char **exec_programs_dirs);
int		validate_infile(char *infile_path);

// ----------- Shared Functions ------------------

int		counting_quotes(char *str, char qtype);
void	free_str(char *str);
char	*ft_itoa(int n);
void	free_arr(char **arr);
char	*get_var_val(int var_index, bool include_eqs);
int		validate_var_name(char *var);
char	**ft_realloc(char **dist, char *str);
void	env_dup(char **env);
int		get_var_index(char *var);
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


t_global_data global_data;

#endif


// FOEIUWGHFEEUHOFUOIU