/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:06:21 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/14 10:07:38 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "arguments/arguments.h"

static void	arguments_option_free(const size_t idx, const t_value val)
{
	(void)idx;
	free(val.value.ptr);
}

void	arguments_destroy(const t_arguments *args)
{
	ft_vector_foreach(&args->options, arguments_option_free);
	ft_vector_free(&args->options);
	ft_vector_free(&args->positional);
}
