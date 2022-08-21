#include "../minishell.h"
/*
TODO:
{
	- echo hello > "${NotExist}" ==> bash: : No such file or directory 
	- echo hello > ${NotExist}  ==> bash: ${NONEXISTENT}: ambiguous redirect
	- echo hello > "${Exist}" ==> simply creat the file with expanded name
	- echo hello > ${Exist}  ==> the same
	- echo hello > ${Exist but it's a directory}  ==> bash: /Users/otoufah/Desktop/Here_we_go: Is a directory
}
*/

int	is_empty(char *str)
{
	int i = -1;

	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] != 32)
		{
			break;
			return (1);
		}
	}
	return (0);
}

void	error_exiting(char *str_1, char *str_2, char *str_3)
{
	ft_putstr_fd(str_1, 2);
	ft_putstr_fd(str_2, 2);
	ft_putstr_fd(str_3, 2);
}
bool    check_parse_errors(t_parse *parse)
{
	size_t i = 0;
	// if (!parse->tokens[i].token && is_empty(parse->tokens[i].token) == 0)
	// {
	// 	ft_putstr_fd("Error\n", 2);
	// 	return TRUE;
	// }
	while (i < parse->tokens->total && parse->tokens[i].token)
	{
		if ((ft_strcmp(parse->tokens[i].type, "here_doc") == 0 && !parse->tokens[i + 1].token) || (ft_strcmp(parse->tokens[i].type, "here_doc") == 0 && (ft_strcmp(parse->tokens[i + 1].type, "delimiter") != 0)))
		{
			error_exiting("Mini: There's no delimiter in front of ", parse->tokens[i].token, "\n");
			global_data.errno_cp = 258;
			return (TRUE);
		}
		else if ((ft_strcmp(parse->tokens[i].type,"red_out") == 0 && !parse->tokens[i + 1].token) || (ft_strcmp(parse->tokens[i].type, "red_out") == 0 && (ft_strcmp(parse->tokens[i + 1].type, "outfile") != 0)))
		{
			error_exiting("Mini: There's no output file in front of red out ", parse->tokens[i].token, "\n");
			global_data.errno_cp = 258;
			return (TRUE);
		}
		else if ((ft_strcmp(parse->tokens[i].type, "append") == 0 && !parse->tokens[i + 1].token) || (ft_strcmp(parse->tokens[i].type, "append") == 0 && (ft_strcmp(parse->tokens[i + 1].type, "app_outfile") != 0)))
		{
			error_exiting("Mini: There's no appended file in front of a append \n", parse->tokens[i].token, "\n");
			global_data.errno_cp = 258;
			return (TRUE);
		}
		else if ((ft_strcmp(parse->tokens[i].type, "red_input") == 0 && !parse->tokens[i + 1].token) || ((ft_strcmp(parse->tokens[i].type, "red_input") == 0) && (ft_strcmp(parse->tokens[i + 1].type, "infile") != 0)))
		{
			error_exiting("Mini: There's no input file to be readead from \n", parse->tokens[i].token, "\n");
			global_data.errno_cp = 258;
			return (TRUE);
		}
		i++;
	}
	return FALSE;
}

/*
	// if there's nothing in piplines
	// if there's no delimiter
	// if there's no output file in red out
	// if there's no appended file to be redirected 
	// if there's no input file to be readead from 
*/