/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_builtin.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:20:00 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 14:22:00 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_BUILTIN_H
# define MSH_BUILTIN_H

typedef struct s_msh	t_msh;

enum					e_builtins
{
	B_CD,
	B_ECHO,
	B_PWD,
	B_EXPORT,
	B_ENV,
	B_UNSET,
	B_EXIT,
};

typedef void			(*t_builtin)(t_msh *prog, int argc, char **argv);

void					ft_cd(t_msh *prog, int argc, char **argv);
void					ft_pwd(t_msh *prog, int argc, char **argv);
void					ft_env(t_msh *prog, int argc, char **argv);
void					ft_echo(t_msh *prog, int argc, char **argv);
void					ft_unset(t_msh *prog, int argc, char **argv);
void					ft_exit(t_msh *prog, int argc, char **argv);
void					ft_export(t_msh *prog, int argc, char **argv);

#endif
