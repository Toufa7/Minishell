/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 09:42:14 by abouchfa         ###   ########.fr       */
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
	[✅] cd = Bad Address
	[✅] unset PATH && cmd : Expected = error msg and exit child proccess
	[✅] echo test > b | << lim | << lim2 creates b before finishing all heredocs: Expected = wait until all heredocs finished
	[✅] echo test > $"" : expected i will say it again please stop at the error the next time i will distroy your father's home iskawatcha
	[✅] non exist command : check the exit_status : it should be 127 not 126
	[✅] exit -1 || exit +1 should exit cleanly without any errors
	[✅] exit without args ==> you should return the last exit_status
	[✅]	$ export a : export a+=Sultan : env : you should assing 
	[✅] cat --> Ctrl + C --> exit 130
	[✅] ctr \ -> quit --> exit 131
	[✅] ignore cntr C in childs
	[❓] Built ins is not working with mulitble pipes: I know why and the solution I just need some rest
	[❓] Bad address when press ctr^D in herdoc

	---> Parser
	[✅] if delimiter has quotes don't expand
	[✅] $fghjm << ls --> cmd should be NUll and ls | "" --> cmd should be empty string : Solution => Simply check if the upcoming input lenght is 0
	[✅] $NOTEXIT ls --> it should run ls 
	[✅] cat << "'"
	[✅] echo ''"'"
	[✅] Using get_var_index to get variable from our env 
	[✅] $NONEXIT return it $UGD => $UGD 
	[✅] Mixing tabs with spaces : Done but check : 
	[✅]	echo $123
	[✅]	echo "$USER ' '  'imad ok"
	{
		[✅] echo "$" =  expected = $
		[✅] echo "$" : Expected = $
		[✅] echo "$_" : Expected = Last Command
		[✅] // echo "$\USER" == $\USER	
		[✅] // echo "\USER"  == \USER	
		[✅] echo $"test"$ : Expected = test$
		[]	$"PWD"
	}
	errors
	{
		- echo hello > "${NotExist}" ==> bash: : No such file or directory 
		- echo hello > ${NotExist}  ==> bash: ${NONEXISTENT}: ambiguous redirect
		- echo hello > "${Exist}" ==> simply creat the file with expanded name
		- echo hello > ${Exist}  ==> the same
		- echo hello > ${Exist but it's a directory}  ==> bash: /Users/otoufah/Desktop/Here_we_go: Is a directory
		if there's nothing in piplines
		if there's no delimiter
		if there's no output file in red out
		if there's no appended file to be redirected 
		if there's no input file to be readead from
	}
	[❓] cat <$k
	[❓] When the varibles in case of > >> < 
	[❓]	export a="ls -la" 
	[❓] env ls => not required
	[❓] pipes : check syntax errors
	[❓] $NONEXIT cmd 
*/

#include "minishell.h"

void	init_global_data(void)
{
	global_data.pre_pipe_infd = -1;
	global_data.size = 0;
	global_data.is_in_herdoc = FALSE;
	global_data.in_fd = 0;
	global_data.out_fd = 1;
	global_data.pre_pipe_infd = -1;
	global_data.last_child_id = 0;
	global_data.parse_error = FALSE;
	global_data.redirection_error = FALSE;
}

void	counting(t_parse *parse)
{
	int	j;

	j = -1;
	while (parse->tokens[++j].token)
		input_counter(parse->tokens, &parse->tokens[j]);
}

void	getting_back(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = handling_quotes(str[i], -1, '|');
}

void	minishell(t_parse *parse)
{
	int	i;

	parse->line_double_quotes = handling_quotes(parse->line, '|', -1);
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
			parse->no_splt = handling_quotes(parse->splt_pipes[i], ' ', -1);
			parse->tokens = spliting_with_spaces(parse->no_splt);
			input_analyse(parse->tokens);
			initializer(parse->tokens);
			counting(parse);
			global_data.parse_error = check_parse_errors(parse);
			if (global_data.parse_error)
				break ;
			parse->pipe_data[i] = get_pipe_data(parse);
		}
		execution(parse->pipe_data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_parse	*parse;

	(void) ac;
	(void) av;
	parse = malloc(sizeof(t_parse));
	global_data.errno_cp = 0;
	signal(SIGINT, parent_sigint);
	signal(SIGQUIT, SIG_IGN);
	env_dup(env);
	while (TRUE)
	{
		init_global_data();
		parse->line = readline("Mini-0.0$ ");
		if (!parse->line)
			exit(global_data.errno_cp);
		add_history(parse->line);
		minishell(parse);
	}
}
