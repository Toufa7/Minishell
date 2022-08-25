/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/25 01:47:29 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

TODO: ✅❓
	--> exection
	[✅] expanding in herdoc
	[✅] cntrl_c in herdoc
	[✅] var witout value should not displayed in env cmd
	[✅] error not displayed when error when giving dir as cmd
	[✅] update exit status
	[✅] Reset Exit status to 0 on succces
	[✅] pwd in a removed dir and unseted path
	[✅] cat | ls : Try to press ok or redirections : Solution => Stop when the user hit enter : Solution simply Try Another Terminal
	[✅] Empty cmd should not display cmd not found
	[✅] do not add PWD and OLDPWD in mcd() Function
	[✅] All s_redirections in one array
	[✅] echo hello > file You should write the output in the file
	[✅] export > file.txt  == SEGV 
	[✅] cat Makefile > outfile.txt < input > outfile_error.txt no such file called input so you should stop a the error file : Solution => Exit in Child Process (if you found an error)
	[✅] < Makdbvbefile << ss cat : You should stop at the error : Solution => Exit in Child Process
	[✅] ambiguous redirect when the file redercs in NULL
	[❓] cat << ss --> Ctrl + C --> exit 130
	[❓] ctr \ -> quit --> exit 131 and CTRL+C retur status it's 1 not 0
	[✅] cd = Bad Address
	[✅] unset PATH && cmd : Expected = error msg and exit child proccess
	[❓] echo test > b | << lim | << lim2 creates b before finishing all heredocs: Expected = wait until all heredocs finished
	[❓] echo test > $"" : expected i will say it again please stop at the error the next time i will distroy your father's home iskawatcha
	[❓] non exist command : check the exit_status : it should be 127 not 126
	[❓] exit -1 || exit +1 should exit cleanly without any errors
	[❓] exit without args ==> you should return the last exit_status
	[❓] ignore cntr C in childs
	[❓]	$ export a : export a+=Sultan : env : you should assing 
 
	---> Parser
	[✅] if delimiter has quotes don't expand
	[✅] $fghjm << ls --> cmd should be NUll and ls | "" --> cmd should be empty string : Solution => Simply check if the upcoming input lenght is 0
	[✅] $NOTEXIT ls --> it should run ls 
	[✅] cat << "'"
	[✅] echo ''"'"
	[✅] Using get_var_index to get variable from our env 
	[❓] $NONEXIT cmd 
	[❓] When the varibles in case of > >> < 
	[❓] $NONEXIT	return it $UGD => $UGD 
	[✅] Mixing tabs with spaces : Done but check : 
	[❓]	export a="ls -la" 
	[❓]	echo $123
	[✅]	echo "$USER ' '  'imad ok"
	[❓] echo "$" =  expected = $
	[❓] echo $"test"$ : Expected = test$
	[❓] echo '$' : Expected = $
	[❓] env ls => not required
	[❓] pipes : check syntax errors
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
	if (!global_data.is_in_herdoc)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		//printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
	global_data.last_child_id = 0;
	global_data.parse_error = FALSE;
}


int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	int		i;
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	global_data.errno_cp = 0;
	rl_catch_signals = 0;
	// Ctrl + C
	signal(SIGINT, control_c);
	// Ctrl + Backslash
	signal(SIGQUIT, SIG_IGN); 
	env_dup(env);
	while (TRUE)
	{
		init_global_data();
		parse->line = readline("Mini-0.0$ ");
		// Ctrl + D
		if (!parse->line)
			exit(global_data.errno_cp);
		add_history(parse->line);
		parse->line_double_quotes = handling_quotes(parse->line, '|', -1);
		// exit(0);
		if (!global_data.parse_error)
		{
			parse->formated_input = input_formating(parse->line_double_quotes);
			parse->splt_pipes = ft_split(parse->formated_input, '|');
			getting_back(parse->splt_pipes);
			i = 0;
			while (parse->splt_pipes[i])
				i++;
			parse->pipe_data = ft_calloc(i + 1, sizeof(t_pipe_data *));
			i = -1;
			while (parse->splt_pipes[++i])
			{
				parse->dont_splt = handling_quotes(parse->splt_pipes[i], ' ', -1);
				parse->tokens = spliting_with_spaces(parse->dont_splt);
				input_analyse(parse->tokens); // Specifying each token his type (delimiter, command, option ...)
				initializer(parse->tokens); counting(parse); // Just fo counting
				//token_and_type(parse);
				global_data.parse_error = check_parse_errors(parse); 
				if (global_data.parse_error)
					break;
				parse->pipe_data[i] = get_pipe_data(parse);
			}
			if (!global_data.parse_error)
				execution(parse->pipe_data);
		}
		// system("leaks Minishell");
	}
}