/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_io.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 15:28:33 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 16:02:20 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_IO_H
# define MSH_IO_H

# include <minishell.h>

enum					e_pipe
{
	READ,
	WRITE,
};

typedef struct s_cmd	t_cmd;

int						in_out_redirection(t_msh *prog, t_cmd *command);
void					close_all(t_vec *fd_arr);
void					close_iostream(int *iostream);
void					close_ifnot(t_vec *fd_arr, int *iostream);
int						set_redirection(t_cmd *command, char **args,
										int *types, t_vec *fd_arr);

#endif
