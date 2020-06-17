/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_cmd.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 15:34:23 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 15:37:11 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_CMD_H
# define MSH_CMD_H

# include <minishell.h>

typedef	struct			s_cmd
{
	char				**args;
	int					*argtypes;
	int					cmdtype;
	int					iostream[2];
	int					cmdpipe[2];
	struct s_cmd		*next;
}						t_cmd;

int						run_commands(t_msh *prog, t_cmd *commands);
int						clear_commands(t_cmd *commands);
t_cmd					*push_command(t_cmd **commands, t_cmd *new);
t_cmd					*new_command(char **argstart, int *types,
									t_vec *fd_arr);
int						get_commands(t_msh *prog, t_tok *tokens,
									size_t totaltokens);

#endif
