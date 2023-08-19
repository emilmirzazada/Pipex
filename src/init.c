/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:29:38 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/15 13:49:53 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

bool	path(char **envp, t_arg *x)
{
	char	*path;

	if (!envp || !*envp)
	{
		path = malloc(sizeof(char) * 14);
		path = "/usr/bin:/bin\0";
		x->path = ft_split(path, ':');
	}
	else
	{
		while (*envp && ft_strncmp(*envp, "PATH", 4))
			++envp;
		path = *envp;
		if (path)
			x->path = ft_split(path + 5, ':');
		else
		{
			path = malloc(sizeof(char) * 14);
			path = "/usr/bin:/bin\0";
			x->path = ft_split(path, ':');
		}
	}
	if (!(x->path))
		return (false);
	return (true);
}

char	*remove_first_lastchr(char *cmd)
{
	cmd = cmd + 1;
	cmd[ft_strlen(cmd) - 1] = 0;
	return (cmd);
}

bool	command(t_arg *x, char *cmd, int i)
{
	int		j;
	char	*corr;
	char	*file;

	x->cmds[i] = ft_cmd_split(cmd);
	if (!(x->cmds[i]))
		return (false);
	j = -1;
	while (!ft_strchr(x->cmds[i][0], '/') && x->path[++j])
	{
		corr = ft_strjoin(x->path[j], "/");
		file = ft_strjoin(corr, x->cmds[i][0]);
		free_set_null((void **)(&corr));
		if (!access(file, F_OK))
		{
			x->file[i] = file;
			return (true);
		}
		free_set_null((void **)(&file));
	}
	x->file[i] = ft_strdup(x->cmds[i][0]);
	if (!(x->file[i]))
		return (false);
	return (true);
}

void	init(t_arg *x, int argc, char *argv[], char **envp)
{
	int	i;

	i = 1;
	x->out = argv[argc - 1];
	x->in = argv[i];
	x->pipe_cnt = argc - 4;
	if (!path(envp, x))
		exit_invalid(x, 0, "invalid envp", NULL);
	if (!ft_dcalloc((void **)(&(x->file)), argc - 2, sizeof(char *)))
		exit_invalid(x, 0, NULL, NULL);
	if (!ft_dcalloc((void **)(&(x->cmds)), argc - 2, sizeof(char **)))
		exit_invalid(x, 0, NULL, NULL);
	while (++i < argc - 1)
	{
		if (!command(x, argv[i], i - 2))
			exit_invalid(x, 0, NULL, NULL);
	}
}
