/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 09:55:45 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/14 10:04:33 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "arguments/arguments.h"

t_result	arguments_add(t_arguments *args, const char *long_name,
				const char short_name, const bool has_value)
{
	t_argument	*argument;

	argument = malloc(sizeof(t_argument));
	if (!argument)
		return (RESULT_ERROR);
	argument->has_value = has_value;
	argument->long_name = long_name;
	argument->short_name = short_name;
	argument->is_set = 0;
	return (ft_vector_push(&args->options, ft_gen_val(TYPE_OTHER,
				(t_any){.ptr = argument})));
}
