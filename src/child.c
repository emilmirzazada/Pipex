/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:03:16 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/16 23:51:19 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	get_here_doc_input(t_arg *x, int fd)
{
	int		res;
	char	*line;

	line = NULL;
	while (true)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		res = get_next_line(STDIN_FILENO, &line);
		if (res == -1)
			exit_invalid(x, errno, NULL, NULL);
		res = (int)ft_strlen(line);
		if (res < (int)ft_strlen(x->limiter))
			res = (int)ft_strlen(x->limiter);
		res = ft_strncmp(line, x->limiter, (size_t)res - 1);
		if (res)
			ft_putstr_fd(line, fd);
		free_set_null((void **)(&line));
		if (!res)
			break ;
	}
	close(fd);
}

void	last_child_proc(char	**envp, t_arg *x, int i)
{
	int	fdout;

	fdout = get_outfile(x);
	dup_fd(x->backup_read_fd, STDIN_FILENO);
	dup_fd(fdout, STDOUT_FILENO);
	close(x->pipe[READ]);
	exec(x, envp, i);
}

void	first_child_proc(char	**envp, t_arg *x, int i)
{
	int	fdin;

	close(x->pipe[READ]);
	if (x->here_doc)
	{
		fdin = open (x->tmp_doc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fdin == -1)
			exit_invalid(NULL, 0, "no such file or directory: ", x->tmp_doc);
		get_here_doc_input(x, fdin);
		fdin = open (x->tmp_doc, O_RDONLY);
		if (fdin == -1)
			exit_invalid(NULL, 0, "no such file or directory: ", x->tmp_doc);
		dup_fd(fdin, STDIN_FILENO);
	}
	else
	{
		fdin = get_infile(x);
		dup_fd(fdin, STDIN_FILENO);
	}
	dup_fd(x->pipe[WRITE], STDOUT_FILENO);
	exec(x, envp, i);
}

void	child_proc(char	**envp, t_arg *x, int i)
{
	if (i == 0)
		first_child_proc(envp, x, i);
	else if (i == x -> pipe_cnt)
	{
		last_child_proc(envp, x, i);
	}
	else
	{
		dup_fd(x->backup_read_fd, STDIN_FILENO);
		dup_fd(x->pipe[WRITE], STDOUT_FILENO);
		close(x->pipe[READ]);
		exec(x, envp, i);
	}
	free_args(x);
	exit(0);
}
