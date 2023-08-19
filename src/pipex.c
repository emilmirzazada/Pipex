/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:38:40 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/15 22:43:49 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_arg	x;

	if (argc == 5)
	{
		ft_memset(&x, 0, sizeof(t_arg));
		init(&x, argc, argv, envp);
		handle_pipes(&x, envp);
	}
	else
	{
		ft_putstr_fd("Invalid number of arguments.\n", 2);
		return (1);
	}
	return (0);
}
