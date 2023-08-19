/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:05:58 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/15 22:54:25 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_set_null(void **ptr)
{
	if (!(ptr && *ptr))
		return ;
	free(*ptr);
	*ptr = NULL;
}

void	free_path(t_arg *x)
{
	int	i;

	i = -1;
	while (x->path[++i])
		free_set_null((void **)(&(x->path[i])));
	free_set_null((void **)(&(x->path)));
}

void	free_file(t_arg *x)
{
	int	i;

	i = -1;
	while (x->file[++i])
		free_set_null((void **)(&(x->file[i])));
	free_set_null((void **)(&(x->file)));
}

void	free_cmds(t_arg *x)
{
	int		i;
	int		j;

	i = -1;
	while (x->cmds[++i])
	{
		j = -1;
		while (x->cmds[i][++j])
			free_set_null((void **)(&(x->cmds[i][j])));
		free_set_null((void **)(&(x->cmds[i])));
	}
	free_set_null((void **)(&(x->cmds)));
}

void	free_args(t_arg *x)
{
	if (!x)
		return ;
	if (x->here_doc && !access(x->tmp_doc, F_OK))
		unlink(x->tmp_doc);
	free_path(x);
	free_file(x);
	free_cmds(x);
}
