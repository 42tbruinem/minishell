/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 16:46:14 by rlucas        #+#    #+#                 */
/*   Updated: 2020/04/29 17:15:23 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

/*
** ft_realloc() creates a new string, copies the contents from a previous
** string, the frees the previous string.
*/

char	*ft_realloc(char *str, size_t newsize)
{
	char	*new;

	new = (char *)ft_calloc(1, newsize);
	if (!new)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(new, str, newsize);
	free(str);
	return (new);
}

/*
** Used to report Env output and to create the prompt.
*/

char		*ft_str3join(const char *s1, const char *s2, const char *s3)
{
	char		*newstring;

	if (!s1 || !s2 || !s3)
		return (NULL);
	newstring = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) +
			ft_strlen(s3) + 1, sizeof(char));
	if (!newstring)
		return (NULL);
	ft_strlcpy(newstring, s1, ft_strlen(s1) + 1);
	ft_strlcpy(newstring + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	ft_strlcpy(newstring + ft_strlen(s1) + ft_strlen(s2), s3, ft_strlen(s3) + 1);
	return (newstring);
}
