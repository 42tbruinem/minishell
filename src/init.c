/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 11:42:21 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/16 16:32:46 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <minishell.h>

void	init_hashtable(t_env table[ENV_SIZE])
{
	size_t		i;

	i = 0;
	while (i < ENV_SIZE)
	{
		table[i].varname = NULL;
		table[i].value = NULL;
		i++;
	}
}

void	init_env(t_msh *prog)
{
	extern char		**environ;
	char			**var;
	char			*varcpy;
	char			*valuecpy;

	var = environ;
	init_hashtable(prog->env);
	while (*var != NULL)
	{
		varcpy = (char *)malloc(ft_strchr(*var, '=') - *var + 1);
		if (!varcpy)
			error_exit(prog, MEM_FAIL);
		ft_strlcpy(varcpy, *var, ft_strchr(*var, '=') - *var + 1);
		valuecpy = (char *)malloc(ft_strlen(ft_strchr(*var, '=')));
		if (!valuecpy)
			error_exit(prog, MEM_FAIL);
		ft_strlcpy(valuecpy, ft_strchr(*var, '=') + 1,
				ft_strlen(ft_strchr(*var, '=')));
		var++;
		if (hashtable_insert(prog->env, varcpy, valuecpy))
			(void)varcpy; /* error message for too many env variables */
		varcpy = NULL;
		valuecpy = NULL;
	}
}

/*
** Old version of init_env using a linked list instead of a hashtable.
*/

/* void	init_env(t_msh **prog) */
/* { */
/* 	extern char		**environ; */
/* 	char			**var; */
/* 	char			*varcpy; */
/*  */
/* 	*prog = (t_msh *)malloc(sizeof(t_msh)); */
/* 	if (!prog) */
/* 		error_exit(*prog, MEM_FAIL); */
/* 	(*prog)->env = NULL; */
/* 	var = environ; */
/* 	while (*var != NULL) */
/* 	{ */
/* 		varcpy = ft_strdup((char *)(*var)); */
/* 		if (!varcpy) */
/* 			error_exit(*prog, MEM_FAIL); */
/* 		if (new_node_at_back(varcpy, &(*prog)->env)) */
/* 			error_exit(*prog, MEM_FAIL); */
/* 		var++; */
/* 		varcpy = NULL; */
/* 	} */
/* } */
