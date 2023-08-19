/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:38:40 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/16 22:57:37 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	handle_here_doc(int *argc, char *argv[], t_arg *x)
{
	int	i;

	i = 1;
	while (++i < *argc)
		argv[i - 1] = argv[i];
	argv[*argc] = NULL;
	*argc = *argc - 1;
	x->here_doc = true;
	x->tmp_doc = "/tmp/.heredoc";
	x->limiter = argv[1];
}

int	main(int argc, char *argv[], char **envp)
{
	t_arg	x;

	if (argc < 5)
	{
		ft_putstr_fd("Invalid number of arguments.\n", 2);
		return (1);
	}
	ft_memset(&x, 0, sizeof(t_arg));
	if (argc > 1 && !ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")))
		handle_here_doc(&argc, argv, &x);
	init(&x, argc, argv, envp);
	handle_pipes(&x, envp);
	free_args(&x);
	return (0);
}
//	valgrind --leak-check=full ./pipex input "grep Hello" "cat -e" "output"
// ./pipex input cat cat ls output 
//< input grep Hello | awk '{count++} END {printf "count: %i", count}' > out
//./pipex inp "grep Hello" 'awk "{count++} END{printf \"count:%i\",count}"' out
// ./pipex input "grep Hello" "cat -e" "wc -l" output
// < /dev/urandom cat | head -1 > output
// ./pipex "/dev/urandom" "cat" "head -1" "output"
//	./pipex here_doc eof cat "cat -e" output  
// ./pipex input "sleep 2" "./a.out" "out" -> i should handle this for minishell
// leaks --atExit -- ./pipex input "grep Hello" "cat -e" "output"
// valgrind --leak-check=full ./pipex input "grep Hello" "cat -e" "output"
// ./pipex input "grep Hello" "cat -e" "output"
// < inputt grep Hello | cat -e > output
// ./pipex input "grep Hello" "awk '{count++} END {print count}'" "output"
// ./pipex "/dev/urandom" "cat" "head -1" "outs/test-xx.txt"
// ./pipex input "grep Hello" "awk '{count++} END {print count}'" output
//	./pipex input "grep Hello" "awk "{count++} END {print count}"" output
//	./pipex input "grep Hello" "awk '\"{count++} END {print count}\"'" output
//	./pipex input "grep Hello" "awk '\"{count++} END {print count}\"'" output
//	7. ./pipex input "grep Hello" "awk '\"{count++} END {print count}\"'" output
//	8. ./pipex input "grep Hello" "awk \"'{count++} END {print count}'\"" output
// the following error is because of script names with space in their name
// 'NoneType' object has no attribute 'stderr'