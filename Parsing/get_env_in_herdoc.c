#include "../minishell.h"

char	*until_doll(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		return (ft_strdup("$"));
	while (str[i] && str[i] != '$')
		i++;
	return (ft_substr(str, 0, i));
}


char	*get_env_in_herdoc(char *target)
{
	int		i;
	char	*output;
	char	*variable;

	i = 0;
	output = ft_strdup("");
	while (target[i])
	{
		if (target[i] == '$')
		{
			if (target[i + 1] == '?')
			{
				variable = ft_itoa(global_data.errno_cp);
				output = ft_strjoin(output, variable);
				i += 2;
			}
			else
			{
				variable = ft_substr(target + i + 1, 0, validate_var_name(target + i + 1));
				output = ft_strjoin(output, getenv(variable));
				i += validate_var_name(target + i + 1) + 1;
			}
		}
		else
		{
			variable = until_doll(target + i);
			i += ft_strlen(variable);
			output = ft_strjoin(output, variable);
		}
		// free_str(variable);
	}
	// free_str(target);
	return output;
}