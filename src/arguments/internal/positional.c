/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 11:45:04 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/14 11:45:23 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments/arguments_internal.h"

t_result	parse_positional(t_arguments *args, char *arg)
{
	const t_value	val = ft_gen_val(TYPE_OTHER, (t_any){.str = (arg)});

	return (ft_vector_push(&args->positional, val));
}
