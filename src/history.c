/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/28 20:29:54 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/28 20:44:52 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <msh_env.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <libft.h>

void	init_history(t_msh *prog)
{
	char	*user;
	int		fd;
	char	*file;
	char	*line;

	user = env_val_get("USER", prog->env, 4);
	if (!user)
	{
		printf("Error retrieving user information.\n");
		return ;
	}
	file = ft_str3join(user, "/", ".msh_history");
	if (!file)
		error_exit(prog, MEM_FAIL);
	fd = open(file, O_RDWR | O_CREAT, 666);
	if (fd == -1 || read(fd, (void *)0, 0) == -1)
	{
		printf("Error opening the history file.\n");
		return ;
	}
	if (!vec_new(&prog->history, sizeof(char *)))
		error_exit(prog, MEM_FAIL);
	while (get_next_line(fd, &line) >= 0)
	{
		if (!vec_add(&prog->history, line))
			error_exit(prog, MEM_FAIL);
	}
	return ;
}
