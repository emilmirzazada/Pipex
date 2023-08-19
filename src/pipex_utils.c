/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 09:10:40 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/15 23:01:19 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_dcalloc(void **ptr, size_t cnt, size_t n)
{
	*ptr = (void *)malloc(cnt * n);
	if (!*ptr)
		return (-1);
	ft_memset(*ptr, 0, cnt * n);
	return (1);
}

int	getexitstatus(int waitstatus)
{
	int	exitstatus;

	if (WIFEXITED(waitstatus))
		exitstatus = WEXITSTATUS(waitstatus);
	else
		exitstatus = WTERMSIG(waitstatus);
	return (exitstatus);
}

char	*ft_removechr(char	*str, char chr)
{
	char	*res;
	int		i;
	int		j;
	int		k;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == chr)
			count++;
	}
	res = malloc(sizeof(char) * (ft_strlen(str) - count + 1));
	j = 0;
	k = 0;
	while (i-- > 0)
	{
		if (str[k] != chr)
			res[j++] = str[k];
		k++;
	}
	res[j] = 0;
	free(str);
	return (res);
}

char	**free_split(char **split)
{
	int	j;

	j = 0;
	while (split[j])
		free(split[j++]);
	free(split[j]);
	free(split);
	return (NULL);
}
