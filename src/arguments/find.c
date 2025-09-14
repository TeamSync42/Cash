/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 09:56:59 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/14 10:03:19 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments/arguments.h"
#include "core/string/ft_string.h"

t_argument	*arguments_find(const t_arguments *args, const char *name)
{
	size_t		i;
	t_value		val;
	t_argument	*arg;

	i = (size_t)-1;
	while (++i < args->options.length)
	{
		val = ft_vector_at(&args->options, (ssize_t)i);
		if (val.type != TYPE_UNDEFINED && val.value.ptr)
		{
			arg = val.value.ptr;
			if (arg->long_name && ft_strcmp(arg->long_name, name) == 0)
				return (arg);
		}
	}
	return (NULL);
}

t_argument	*arguments_find_short(const t_arguments *args, const char name)
{
	size_t		i;
	t_value		val;
	t_argument	*arg;

	i = (size_t)-1;
	while (++i < args->options.length)
	{
		val = ft_vector_at(&args->options, (ssize_t)i);
		if (val.type != TYPE_UNDEFINED && val.value.ptr)
		{
			arg = val.value.ptr;
			if (arg->short_name == name)
				return (val.value.ptr);
		}
	}
	return (NULL);
}
