/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_redirection.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/04 19:35:57 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 20:03:51 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <msh_lex.h>
#include <msh_io.h>
#include <msh_cmd.h>

static	int		is_redir(int type)
{
	return (type == APPENDFILE ||
		type == WRITEFILE ||
		type == INPUT_SENDER);
}

static	int		new_file(t_cmd *command, char **args, int type, t_vec *fd_arr)
{
	int	fd;

	fd = -1;
	if (!args[0])
		return (0);
	if (type == WRITEFILE)
		fd = open(args[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPENDFILE)
		fd = open(args[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (type == INPUT_SENDER)
		fd = open(args[0], O_RDONLY);
	if (fd == -1 || !vec_add(fd_arr, &fd))
		return (0);
	if (type == INPUT_SENDER)
		command->iostream[READ] = fd;
	else
		command->iostream[WRITE] = fd;
	args[0] = NULL;
	if (command->args[0] == args[0])
		command->args++;
	return (1);
}

int				set_redirection(t_cmd *command, char **args,
								int *types, t_vec *fd_arr)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (is_redir(types[i]))
			if (!new_file(command, &args[i], types[i], fd_arr))
				return (0);
		i++;
	}
	return (1);
}
