/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 13:51:05 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/16 23:07:37 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	dup_fd(int dst, int src)
{
	int		fd;

	fd = dup2(dst, src);
	close(dst);
	if (fd == -1)
	{
		exit_invalid(NULL, errno, NULL, NULL);
	}
}

int	get_infile(t_arg *x)
{
	int	fdin;

	if (access(x->in, F_OK))
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(x->in, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_args(x);
		exit(1);
	}
	fdin = open(x->in, O_RDONLY);
	if (fdin < 0)
		exit_invalid(x, 0, "no such file or directory: ", x->in);
	return (fdin);
}

int	get_outfile(t_arg *x)
{
	int	fdout;

	fdout = open(x->out, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fdout < 0)
		exit_invalid(x, 0, "no such file or directory: ", x->out);
	return (fdout);
}
