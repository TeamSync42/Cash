/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:56:07 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/02 15:02:42 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include "libft.h"

t_result	arguments_add(t_arguments *args, const char *long_name,
				char short_name, _Bool has_value)
{
	t_result	result;
	t_argument	*argument;

	argument = malloc(sizeof(t_argument));
	if (!argument)
		return (RESULT_ERROR);
	argument->has_value = has_value;
	argument->long_name = long_name;
	argument->short_name = short_name;
	argument->is_set = 0;
	result = ft_vector_push(&args->options, ft_gen_val(TYPE_OTHER,
		(t_any){ .ptr = argument }));
	return (result);
}
