/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   evaluate_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 13:10:59 by rlucas        #+#    #+#                 */
/*   Updated: 2020/06/22 14:14:30 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>
#include <msh_lex.h>
#include <msh_env.h>

static void		add_tilde_value(t_lexer *lex, t_vecstr *line,
							size_t env_name_len, t_msh *prog)
{
	char	*home;
	char	*user;

	home = env_val_get("HOME", prog->env, 4);
	if (!home)
	{
		if (vecstr_insert_str(line, lex->i, " "))
			error_exit(prog, MEM_FAIL);
		lex->state = lex_checkstate(vecstr_val(line, lex->i), *lex);
		vecstr_set(line, lex->i, '\0');
		return ;
	}
	if (vecstr_slice(line, lex->i, lex->i + env_name_len + 1))
		error_exit(prog, MEM_FAIL);
	if (env_name_len > 1)
	{
		user = ft_strsdup(&line->str[lex->i + 1], " \";<>.|\'");
		home = ft_str3join("/Users", "/", user);
		free(user);
	}
	if (vecstr_insert_str(line, lex->i, home))
		error_exit(prog, MEM_FAIL);
	lex->i = lex->i + ft_strlen(home) - ((env_name_len > 1) ? 0 : 1);
	if (env_name_len > 1)
		free(home);
}

static void		add_env_value(t_lexer *lex, t_vecstr *line, size_t env_name_len,
		t_msh *prog)
{
	char		*env_value;

	env_value = env_val_get(vecstr_get(line) + lex->i + 1,
			prog->env, env_name_len);
	if (vecstr_slice(line, lex->i, lex->i + env_name_len + 1))
		error_exit(prog, MEM_FAIL);
	if (!env_value)
	{
		if (lex->state != INDOUBLEQUOTE)
		{
			if (vecstr_insert_str(line, lex->i, " "))
				error_exit(prog, MEM_FAIL);
			lex->state = lex_checkstate(vecstr_val(line, lex->i), *lex);
			vecstr_set(line, lex->i, '\0');
		}
		return ;
	}
	else if (vecstr_insert_str(line, lex->i, env_value))
		error_exit(prog, MEM_FAIL);
	lex->i = lex->i + ft_strlen(env_value) - 1;
	if (lex->state != INDOUBLEQUOTE)
		lex->state = NORMAL;
}

static void		expand_tilde(t_lexer *lex, t_vecstr *line, t_msh *prog)
{
	char	*user;
	size_t	username_len;

	user = vecstr_get(line) + lex->i + 1;
	username_len = env_strclen(user);
	add_tilde_value(lex, line, username_len, prog);
}

static void		expand_env_value(t_lexer *lex, t_vecstr *line, t_msh *prog)
{
	size_t		env_name_len;
	char		*env_name;

	env_name = vecstr_get(line) + lex->i + 1;
	env_name_len = env_strclen(env_name);
	if (lex->state == INDOUBLEQUOTE &&
			ft_strclen(env_name, '"') < env_name_len)
		env_name_len = ft_strclen(env_name, '"');
	add_env_value(lex, line, env_name_len, prog);
}

void			evaluate_env(t_lexer *lex, t_vecstr *line, t_msh *prog)
{
	int		c;

	c = vecstr_val(line, lex->i + 1);
	if (vecstr_val(line, lex->i) == '~')
		expand_tilde(lex, line, prog);
	if (c == 0)
		return ;
	if (c == '(')
		(void)line;
	if (c == '$')
		env_current_process(lex, line, prog);
	if (c == '?')
	{
		env_exitstatus(lex, line, prog);
		return ;
	}
	if (ft_isalnum(c) || c == '_')
		expand_env_value(lex, line, prog);
}
