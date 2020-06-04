/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/04 19:35:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/04 12:18:32 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

void	close_all(t_vec *fd_arr)
{
	int		*fds;
	size_t	i;

	i = 0;
	fds = (int *)fd_arr->store;
	while (i < fd_arr->index)
	{
		close(fds[i]);
		i++;
	}
}

void	close_ifnot(t_vec *fd_arr, int *iostream)
{
	size_t	i;
	int		*fds;

	i = 0;
	fds = (int *)fd_arr->store;
	while (i < fd_arr->index)
	{
		if (fds[i] != -1 &&
			(fds[i] != iostream[READ] && fds[i] != iostream[WRITE]))
			close(fds[i]);
		i++;
	}
}

void	close_iostream(int *iostream)
{
	if (iostream[READ] != -1)
		close(iostream[READ]);
	if (iostream[WRITE] != -1)
		close(iostream[WRITE]);
}

int		is_redir(int type)
{
	return (type == APPENDFILE ||
		type == WRITEFILE ||
		type == INPUT_SENDER);
}

void	print_filearr(t_vec *fd_arr)
{
	int		*fds;
	size_t	i;

	i = 0;
	fds = (int *)fd_arr->store;
	while (i < fd_arr->index)
	{
		dprintf(2, "[%d]%c", fds[i], (i + 1 < fd_arr->index) ? ' ' : '\n');
		i++;
	}
}

int		new_file(t_cmd *command, char **args, int type, t_vec *fd_arr)
{
	int	fd;

	fd = -1;
	if (type == WRITEFILE)
		fd = open(args[0], O_CREAT | O_WRONLY | O_TRUNC);
	else if (type == APPENDFILE)
		fd = open(args[0], O_CREAT | O_WRONLY | O_APPEND);
	else if (type == INPUT_SENDER)
		fd = open(args[0], O_RDONLY);
	if (fd == -1 || !vec_add(fd_arr, &fd))
		return (0);
	if (type == INPUT_SENDER)
		command->iostream[READ] = fd;
	else
		command->iostream[WRITE] = fd;
	args[0] = NULL;
	return (1);
}

int		new_stream(t_cmd *cmd, char **args, int type, t_vec *fd_arr)
{
	if (!args[0])
	{
		dprintf(2, "banaantjes\n");
		return (0); //error
	}
//	return (1);
	return (new_file(cmd, args, type, fd_arr));
}

int		set_redirection(t_cmd *command, char **args, int *types, t_vec *fd_arr)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (is_redir(types[i])) //check if it's a redirection
			if (!new_stream(command, &args[i], types[i], fd_arr))
				return (0);
		i++;
	}
	return (1);
}
