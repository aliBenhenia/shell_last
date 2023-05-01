// #include "minishell.h"


// void do_sigint(int capt)
// {
// 	if (capt == SIGINT )
// 	{
// 		g_var.exit_state = 1;
// 		rl_on_new_line();
// 		write(1, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }
// void do_sigquit(int capt)
// {
// 	if (capt == SIGQUIT)
// 		;
// }

// int sig_handler(void)
// {
//     void	*ret1;
// 	void	*ret2;

// 	ret1 = signal(SIGINT, do_sigint);
// 	ret2 = signal(SIGQUIT, do_sigquit);
// 	if (ret1 == SIG_ERR || ret2 == SIG_ERR)
// 		return(printf("Error in signals ..."), exit(1), 1);
// 	return (0);
// }