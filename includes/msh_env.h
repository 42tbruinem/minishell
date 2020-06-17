/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_env.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 13:25:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/06/17 14:22:23 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_ENV_H
# define MSH_ENV_H

# include <sys/types.h>
# include "minishell.h"

typedef	struct			s_var
{
	char				*name;
	char				*val;
	size_t				len;
	struct s_var		*next;
}						t_var;

typedef struct s_msh	t_msh;

void					env_del(t_var *delete);
t_var					*env_new(const char *name, const char *val);
void					env_print(t_var *env);
void					env_update(t_msh *prog);
void					env_unset(t_var **env, char *name);
char					**env_convert(t_var *env);
t_var					*env_val_set(const char *name, t_var *env,
									const char *val);
int						env_init(t_msh *prog);
char					*env_val_get(const char *name, t_var *env);
int						env_clear(t_var *env, void (*del)(void *));

#endif
