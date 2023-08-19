/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:09:05 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/16 23:42:17 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// void	print_arr(int	*arr)
// {
// 	int	i;

// 	i = 0;
// 	while (i < arr[i])
// 	{
// 		ft_putnbr_fd(arr[i], 2);
// 		ft_putstr_fd("\n", 2);
// 		i++;
// 	}
// }
void	close_readends(t_arg *x)
{
	int	i;

	i = 0;
	while (x->backup_readends[i])
	{
		close(x->backup_readends[i]);
		i++;
	}
}

void	wait_for_childs(t_arg *x)
{
	int		status;
	int		j;
	int		last_status;

	j = x->pipe_cnt;
	last_status = 0;
	while (j >= 0)
	{
		waitpid(x->pids[j], &status, 0);
		if (j == x->pipe_cnt && !x->here_doc)
		{
			if (!x->here_doc)
			{
				close_readends(x);
				exit(getexitstatus(status));
			}
			else
				last_status = getexitstatus(status);
		}
		j--;
	}
	exit(last_status);
}

void	parent_proc(t_arg *x, int i)
{
	close(x->pipe[WRITE]);
	x->backup_read_fd = x->pipe[READ];
	x->backup_readends[i] = x->pipe[READ];
	if (i == x->pipe_cnt)
		wait_for_childs(x);
}
