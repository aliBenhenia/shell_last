/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:38:01 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/17 22:40:47 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	handle_exit_status(t_cmd_line *cmd_line, int pid)
{
		int built_code;
		int	a;

		built_code = builtins((cmd_line)->str[0]);
		if(built_code == 0)
		{
			if (1)
			{
				waitpid(pid, &a, 0);
				if (WIFEXITED(a))
				{
					//printf("----.>%d\n",g_var.exit_state);
					g_var.exit_state = WEXITSTATUS(a);
					printf("----.>%d\n",g_var.exit_state);
					// g_var.exit_state = 0;
				}
				else if (WIFSIGNALED(a))
				{
					g_var.exit_state = WTERMSIG(a) + 128;
					printf("-->%d\n",g_var.exit_state);
				}
			}
		}
}
void execute_command(t_cmd_line **cmd_line, t_env_list **env_list, int **fd, t_export **export)
{
	t_cmd_line *cmd_tmp = *cmd_line;
	int no_file = 1;
	t_redirections	*l_infile;
	t_redirections	*l_outfile;
	t_cmd_line *temp;
	int i = 0;
	int flg = 0;
	pid_t	pid;
	int	heredoc_fd;
	while (cmd_tmp)
	{
		if (cmd_tmp->separator == e_pipe)
		{
			pipe(fd[i]);
			flg = 1;
		}
		ft_heredoc(&cmd_tmp, &heredoc_fd);
		if (!(pid = fork()))
		{
			l_infile = last_infile(&cmd_tmp, &no_file);
			if (!no_file)
				return ;
			l_outfile = last_outfile(&cmd_tmp);
			if (flg)
				dup_to_pipe(fd, i, count_list(cmd_line));
			if (l_outfile)
				dup_outfile(l_outfile);
			if (l_infile)
				dup_infile(l_infile);
			execute_command_2(&cmd_tmp, env_list, export, pid);
		}
		temp = cmd_tmp;
		close_pipes(fd , i, count_list(cmd_line), flg);
		cmd_tmp = cmd_tmp->next;
		i++;
	}
	handle_exit_status(temp, pid);
	while (wait(0) != -1);
}

void execution(t_cmd_line **cmd_line, t_env_list **env_list,t_export **export_list)
{
	if ((*cmd_line) && main_builtins(cmd_line) && (*cmd_line)->separator == e_nline)
	{
		int	fd;
		ft_heredoc(cmd_line, &fd);
		execute_builtins(cmd_line, env_list,export_list);
	}
	else if ((*cmd_line))
	{
		int **fd = malloc(sizeof(int *) * count_list(cmd_line));
		int i = 0;
		while (i < count_list(cmd_line))
			fd[i++] = malloc(sizeof(int) * 2);
		execute_command(cmd_line, env_list, fd, export_list);
	}
}