/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:47:19 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/15 12:40:58 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	handle_pipes(t_arg *x, char *envp[])
{
	int		i;
	int		pid;

	i = -1;
	while (++i <= x->pipe_cnt)
	{
		if (pipe(x->pipe) == -1)
			exit_invalid(x, 0, NULL, NULL);
		pid = fork();
		if (pid == -1)
			exit_invalid(x, 0, NULL, NULL);
		else if (!pid)
		{
			child_proc(envp, x, i);
		}
		else
		{
			x->pids[i] = pid;
			parent_proc(x, i);
		}
	}
}

void	exec(t_arg *x, char	**envp, int i)
{
	int	len;

	len = ft_strlen(x->file[i]);
	if (ft_strchr(x->file[i], '\\'))
		x->file[i] = ft_removechr(x->file[i], '\\');
	if (!ft_strchr(x->file[i], '/') && x->file[i][0] != '.'
		&& ft_strncmp(ft_substr(x->file[i], len - 2, len), "sh", 2) == 0)
	{
		x->file[i] = NULL;
	}
	if (execve(x->file[i], x->cmds[i], envp) == -1)
	{
		if (!access(x->file[i], F_OK))
		{
			free_args(x);
			exit (126);
		}
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(x->cmds[i][0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_args(x);
		exit (127);
	}
}
