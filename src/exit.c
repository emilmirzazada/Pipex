/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:27:37 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/14 18:59:16 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exit_invalid(t_arg *x, int code, char *msg1, char *msg2)
{
	int		fd;

	if (x && x->out && access(x->out, F_OK) == -1)
	{
		fd = open(x->out, O_CREAT | O_WRONLY, 0644);
		if (fd != -1)
			close(fd);
	}
	if (x)
		free_args(x);
	if (msg1)
	{
		ft_putstr_fd(msg1, 2);
		ft_putstr_fd(msg2, 2);
	}
	else if (code)
	{
		ft_putstr_fd(strerror(code), 2);
		exit (code);
	}
	else
		ft_putstr_fd(strerror(errno), 2);
	exit(1);
}
