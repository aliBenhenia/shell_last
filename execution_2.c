/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 14:07:54 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/13 16:01:06 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(char	*cmd)
{

	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (2);
	if (!ft_strcmp(cmd, "pwd"))
		return (3);
	if (!ft_strcmp(cmd, "export"))
		return (4);
	if (!ft_strcmp(cmd, "env"))
		return (5);
	if (!ft_strcmp(cmd, "unset"))
		return (6);
	return (0);
}

void    print_env(t_env_list *list, int flag)
{
    t_env_list *head = list;
    g_var.exit_state = 0;
    while (head)
    {
        if(ft_strcmp(head->value,"") == 0)
            printf("%s\n",head->name);
        else
            printf("%s=\"%s\"\n",head->name,head->value);
            head = head->next;
    }
    if (flag)
        exit(0);
}

void	exec_builtins(char	**str, t_env_list **env_list, int code, t_export **export)
{
    if (code == 1)
        ft_echo(str, 1);
	if (code == 2)
		ft_cd(str[1], env_list, 1);
	if (code == 3)
		ft_pwd(1);
	else if (code == 4)
        do_export(str, export, env_list, 1);
    else if(code == 5)
        print_env(*env_list, 1);
    else if (code == 6)
        do_unset(str, export, env_list, 1);
}

int main_builtins(t_cmd_line **cmd_line)
{
    if ((*cmd_line) && (*cmd_line)->str[0])
    {
        if (!ft_strcmp((*cmd_line)->str[0], "cd"))
            return (1);
        if (!ft_strcmp((*cmd_line)->str[0], "export") && (*cmd_line)->str[1] != NULL)
            return (1);
        if (!ft_strcmp((*cmd_line)->str[0], "unset"))
            return (1);
    }
    return (0);
}

void    execute_builtins(t_cmd_line **cmd_line, t_env_list **env_list,t_export **export_list)
{
    if (!ft_strcmp((*cmd_line)->str[0], "cd"))
        ft_cd((*cmd_line)->str[1], env_list, 0);
    if (!ft_strcmp((*cmd_line)->str[0], "export"))
       do_export((*cmd_line)->str,export_list,env_list, 0);
    if (!ft_strcmp((*cmd_line)->str[0], "unset"))
        do_unset((*cmd_line)->str,export_list,env_list, 0);
}