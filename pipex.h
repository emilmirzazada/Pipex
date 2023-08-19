/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:40:01 by emirzaza          #+#    #+#             */
/*   Updated: 2023/08/16 00:11:49 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>

# define STD_IN 0
# define STD_OUT 1

# define READ 0
# define WRITE 1

typedef struct s_arg
{
	int			pipe[2];
	int			backup_read_fd;
	char		*in;
	char		*out;
	int			pipe_cnt;
	char		***cmds;
	char		**file;
	char		**path;
	bool		here_doc;
	char		*tmp_doc;
	char		*limiter;
	int			pids[1064];
	int			backup_readends[1064];
}				t_arg;

void	handle_pipes(t_arg *x, char *envp[]);
void	exec(t_arg *x, char	**env, int i);
void	init(t_arg *x, int argc, char *argv[], char **envp);
void	child_proc(char	**envp, t_arg *x, int i);
void	parent_proc(t_arg *x, int i);
int		getexitstatus(int waitstatus);
char	**ft_cmd_split(char *s);
// exit
void	exit_invalid(t_arg *x, int code, char *msg1, char *msg2);
//path
char	*find_path(char **envp);
char	*get_cmd_path(char **paths, char *cmd);
//file
int		get_infile(t_arg *x);
int		get_outfile(t_arg *x);
void	dup_fd(int dst, int src);
// special chars
bool	ft_isspace(int c);
bool	ft_mode_equal(char *m1, char *m2, int len);
bool	ft_mode_diff(char *m1, char *m2, int len);
void	ft_shift_special_chr(char **s, char *mode);
char	*ft_check_special_chr(int c1, int c2, int c0);
//free
int		ft_dcalloc(void **ptr, size_t cnt, size_t n);
void	free_set_null(void **ptr);
void	free_args(t_arg *x);
char	**free_split(char **split);
void	free_file(t_arg *x);
void	free_path(t_arg *x);
void	free_cmds(t_arg *x);
//helpers
char	*ft_removechr(char	*str, char chr);

#endif