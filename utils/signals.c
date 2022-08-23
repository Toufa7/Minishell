#include "../minishell.h"

void	control_c(int sig)
{
	if (sig == SIGINT && !global_data.is_in_herdoc)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}