/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 22:31:13 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/17 02:48:39 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void dup_to_pipe(int **fd, int i, int cmds)
{
	if (i == 0)
	{
		dup2(fd[i][1], 1);
		close(fd[i][0]);
		close(fd[i][1]);
	}
	else if (i + 1 == cmds)
	{
		dup2(fd[i - 1][0], 0);
		close(fd[i - 1][0]);
	}
	else if (i > 0 && i + 1 < cmds)
	{
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
		close(fd[i - 1][0]);
		close(fd[i][1]);
		close(fd[i][0]);
	}
}

void	close_pipes(int **fd, int i, int cmds, int flag)
{
	if (flag != 1)
		return ;
	if (i == 0)
		close(fd[i][1]);
	else if (i + 1 == cmds)
		close(fd[i - 1][0]);
	else if (i > 0 && i + 1 < cmds)
	{
		close(fd[i][1]);
		close(fd[i - 1][0]);
	}
}

void execute_command_2(t_cmd_line **cmd_line, t_env_list **env_list, t_export **export, int pid)
{
	int built_code;

	built_code = builtins((*cmd_line)->str[0]);
	if (built_code)
	{
		exec_builtins((*cmd_line)->str, env_list, built_code,export);
	}
	else
	{
		execve_func((*cmd_line)->str, env_list);
	}
}

void execve_func(char **cmd, t_env_list **env_list)
{
	char **path;
	char *cmd_;
	char **envp;


	path = get_path(env_list);
	cmd_ = check_command_in_path(path, cmd[0]);
	envp = create_envp(env_list);
	if (ft_strchr(cmd[0], '/'))
		execve(cmd[0], cmd, envp);
	if (!cmd_)
	{
		g_var.exit_state = 127;
		printf("-->%d\n",g_var.exit_state);
		write( 1, "minishell: ", ft_strlen("minishell: "));
		write (1, "Command not found\n", ft_strlen("Command not found\n"));
		exit(g_var.exit_state);
	}
	execve(cmd_, cmd, envp);
	// exit(g_var.exit_state);

}

char *check_command_in_path(char **path, char *cmd)
{
	int i;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		if (!access(ft_strjoin(path[i], cmd), F_OK))
		{
			return (ft_strjoin(path[i], cmd));
			break;
		}
		i++;
	}
	return (NULL);
}