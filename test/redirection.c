/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/02 15:10:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/05/06 12:34:05 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int		main(void)
{
	int			pid;
	int			pipefd[2];
	static char	buff[5];

	pipe(pipefd);
	pid = fork();
	if (!pid)
	{
//		dprintf(pipefd[1], "hoi\n");
//		close(pipefd[0]); //important
	}
	close(pipefd[1]); //important
	read(pipefd[0], buff, 4);
	printf("%s", buff);
	return (0);
}
