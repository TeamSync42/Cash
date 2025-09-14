/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 09:57:17 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/14 10:17:27 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments/arguments.h"

bool	arguments_is_set(const t_arguments *args, const char *name)
{
	const t_argument	*arg = arguments_find(args, name);

	if (!arg)
		return (0);
	return (arg->is_set);
}

char	*arguments_get(const t_arguments *args, const char *name)
{
	const t_argument	*arg = arguments_find(args, name);

	if (!arg)
		return (NULL);
	return (arg->value);
}
