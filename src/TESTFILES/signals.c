/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 16:51:05 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/16 16:52:03 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
/* #include <signal.h> */

/* Signals: */
/* SIGINT = CTRL-C */
/* SIGTERM = kill (pid) OR kill -TERM (pid) */
/* SIGKILL = kill -KILL (pid) OR kill -9 (pid) */
/* SIGKILL cannot be handled */
/* SIGSEGV = segmentation fault */

/* STOP and CONT are also signals that can be sent with kill. */
/* User defined signals can also be sent */

/* Handling a segmentation fault can be done, but then the program just */
/* tries to perform the segmentation fault operation again. */

/* void	sig_handler(int num) */
/* { */
/* 	(void)num; */
/* 	write(1, "I\nam\ninevitable\n", 16); */
/* } */

int		main(void)
{
	/* signal(SIGINT, sig_handler); */
	/* signal(SIGTERM, sig_handler); */
	while (1)
	{
		printf("hiya\n");
		sleep(1);
	}
	return (0);
}
