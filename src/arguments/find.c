/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:10:31 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/02 15:21:26 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include "libft.h"

t_argument	*arguments_find(t_arguments *args, const char *name)
{
	size_t		i;
	t_value		val;
	t_argument	*arg;

	i = -1;
	while (++i < args->options.length)
	{
		val = ft_vector_at(&args->options, i);
		if (val.type != TYPE_UNDEFINED && val.value.ptr)
		{
			arg = val.value.ptr;
			if (arg->long_name && ft_strcmp(arg->long_name, name) == 0)
				return (arg);
		}
	}
	return (NULL);
}

t_argument	*arguments_find_short(t_arguments *args, char name)
{
	size_t	i;
	t_value	val;

	i = -1;
	while (++i < args->options.length)
	{
		val = ft_vector_at(&args->options, i);
		if (val.type != TYPE_UNDEFINED && val.value.ptr)
		{
			if (((t_argument *)val.value.ptr)->short_name == name)
				return (val.value.ptr);
		}
	}
	return (NULL);
}
