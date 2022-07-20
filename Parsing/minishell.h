/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:39:43 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/02 22:39:44 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./Libft/libft.h"

# define GREEN "\033[32m"
# define RESET "\033[0m"
# define TRUE 1
# define FALSE 0
# define PATH_MAX  4096

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
	char	**doc_infile;
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

char		*get_env_variables(char	**env, char	*target);
char		**pipes(char	*str);
char		*input_formating(char	*str);
void		input_analyse(t_tokens	*tokens);
t_tokens	*spliting_with_spaces(char	*str);
void		input_counter(t_tokens	*counter, t_tokens	*tokens);
void		initializer(t_tokens	*tokens);
void		input_types(t_parse	*parse);

#endif