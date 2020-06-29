/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_builtin.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 14:20:00 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/29 13:35:00 by tbruinem      ########   odam.nl         */
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

typedef int				(*t_builtin)(t_msh *prog, int argc, char **argv);

int						builtin_error(char **argv);
char					*get_cwd(void);
int						ft_cd(t_msh *prog, int argc, char **argv);
int						ft_pwd(t_msh *prog, int argc, char **argv);
int						ft_env(t_msh *prog, int argc, char **argv);
int						ft_echo(t_msh *prog, int argc, char **argv);
int						ft_unset(t_msh *prog, int argc, char **argv);
int						ft_exit(t_msh *prog, int argc, char **argv);
int						ft_export(t_msh *prog, int argc, char **argv);

#endif
