/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/17 15:23:33 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

TODO: ✅❓
	[✅] expanding in herdoc
	[✅] cntrl_c in herdoc
	[✅] var witout value should not displayed in env cmd
	[✅] error not displayed when error when giving dir as cmd
	[✅] update exit status
	[❓] Create 
	[❓] Reset Exit status to 0 on succces
	[❓] pwd in a removed dir and unseted path
	[❓] BAD Address error
	[❓] Program hanging when dealing with std_in and std_out
*/

#include "minishell.h"

void	token_and_type(t_parse *parse)
{
	int i = -1;
	while (parse->tokens[++i].token)
	{
		printf("Token -> %s -> Type -> %s\n",parse->tokens[i].token,parse->tokens[i].type);
	}
}

void	counting(t_parse *parse)
{
	int j = -1;
	while (parse->tokens[++j].token)
		input_counter(parse->tokens, &parse->tokens[j]);
}

void	getting_back(char **str)
{
	int i = -1;
	while (str[++i])
		str[i] = handling_quotes(str[i], -1, '|');
}

void	control_c(int sig)
{
	if (sig == SIGINT)
	{
		if (!global_data.is_in_herdoc)
		{
			printf("\n");
			// rl_on_new_line();
			// rl_replace_line("", 0);
			// rl_redisplay();
		}
		else
			exit(1);
	}
}

void	init_global_data()
{
	global_data.pre_pipe_infd = -1;
	global_data.size = 0;
	global_data.is_in_herdoc = FALSE;
	global_data.in_fd = 0;
	global_data.out_fd = 1;
	global_data.pre_pipe_infd = -1;
	global_data.errno_cp = 0;
	global_data.last_child_id = 0;
	global_data.parse_error = FALSE;
}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_parse *parse;

	parse = malloc(sizeof(t_parse));
	env_dup(env);
	while (TRUE)
	{
		signal(SIGINT, control_c); // Ctrl+C
		signal(SIGQUIT, SIG_IGN); // Ctrl + Backslash
		parse->line = readline(GREEN "Mini-0.0$ " RESET);
		add_history(parse->line);
		if (!parse->line || ft_strcmp(parse->line, "exit") == 0) // Ctrl + D 
			exit(0);
		parse->line_double_quotes = handling_quotes(parse->line, '|', -1);
		if (!global_data.parse_error)
		{
			parse->formated_input = input_formating(parse->line_double_quotes);
			parse->splt_pipes = ft_split(parse->formated_input, '|');
			getting_back(parse->splt_pipes);
			int i = 0;
			while (parse->splt_pipes[i])
				i++;
			parse->pipe_data = ft_calloc(i + 1, sizeof(t_pipe_data *));
			i = -1;
			while (parse->splt_pipes[++i])
			{
				parse->dont_splt = handling_quotes(parse->splt_pipes[i], ' ', -1);
				parse->tokens = spliting_with_spaces(parse->dont_splt);
				input_analyse(parse->tokens);
				initializer(parse->tokens);
				counting(parse);
				global_data.parse_error = check_parse_errors(parse);
				if (global_data.parse_error)
					break;
				parse->pipe_data[i] = get_pipe_data(parse);
			}
			if (!global_data.parse_error)
				execution(parse->pipe_data);
		}
	}
}