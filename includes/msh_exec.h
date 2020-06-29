/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_exec.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 15:36:19 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/29 13:32:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXEC_H
# define MSH_EXEC_H

# include <minishell.h>
# include <msh_cmd.h>

typedef struct s_var	t_var;

void					execute(t_msh *prog, t_cmd *cmd);
char					*get_program(char **args, int *types);
int						run_builtin(t_msh *prog, t_cmd *cmd, int id);
void					run_program(t_msh *prog, t_cmd *cmd, char *abspath);
void					get_abspath(char *program, char **abspath_to_exe,
								t_var *env);

#endif
