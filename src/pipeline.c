/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/04 19:35:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/05/04 20:17:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int		is_redir(int type)
{
	return (type == APPEND ||
		type == TRUNC ||
		type == IN_REDIR ||
		type == PIPE);
}

int		new_file(char *filename, int flag, t_vec *fd_arr)
{
	int	fd;

	if (open(filename, flag) == -1 || !vec_add(fd_arr, &fd))
		return (0);
	return (1);
}

int		new_stream(char **args, int type, t_vec *fd_arr)
{
	int		newfd;
	int		newpipe[2];

	if (!args[1])
		return (0);
	if (type == PIPE)
	{
		if (pipe(newpipe) == -1 || !vec_add(fd_arr, &newpipe[READ]) ||
		!vec_add(fd_arr, &newpipe[WRITE]))
			return (0);
		return (1);
	}
	if (type == APPEND)
		return (new_file(args[1], O_CREAT | O_WRONLY | O_APPEND, fd_arr));
	if (type == TRUNC)
		return (new_file(args[1], O_CREAT | O_WRONLY | O_APPEND, fd_arr));
	if (type == IN_REDIR)
		return (new_file(args[1], O_RDONLY, fd_arr));
	return (1);
}

int		create_pipeline(t_vec *vec_arg, t_vec *vec_types, t_vec *fd_arr)
{
	size_t	i;
	char	**args;
	int		*types;

	i = 0;
	vec_new(fd_arr, sizeof(int));
	args = (char **)vec_arg->store;
	types = (int *)vec_types->store;
	if (!vec_new(fd_arr, sizeof(int)))
		return (0);
	while (args[i])
	{
		if (is_redir(types[i]))
			if (new_stream(&args[i], types[i], fd_arr))
				return (0);
		i++;
	}
}
