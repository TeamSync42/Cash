/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 09:57:25 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/14 10:22:14 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments/arguments.h"
#include "arguments/arguments_internal.h"

static int	get_size(const int argc)
{
	if (argc > 8)
		return (argc / 2);
	return (4);
}

#ifdef _DEBUG

static t_result	arguments_init_debug(t_arguments *args)
{
	if (arguments_add(args, "disassemble", 'd', 0) != RESULT_OK)
		return (RESULT_ERROR);
	return (RESULT_OK);
}

#else

static t_result	arguments_init_debug(const t_arguments *args)
{
	(void)args;
	return (RESULT_OK);
}

#endif

t_result	arguments_init(t_arguments *args, const int argc, char **argv)
{
	const int	size = get_size(argc);

	args->name = argv[0];
	if (ft_vector_init(&args->positional, (size_t)size) != RESULT_OK
		|| ft_vector_init(&args->options, (size_t)size) != RESULT_OK
		|| arguments_add(args, "posix", 0, 0) != RESULT_OK
		|| arguments_add(args, "verbose", 'v', 0) != RESULT_OK
		|| arguments_add(args, NULL, 'c', 1) != RESULT_OK
		|| arguments_init_debug(args) != RESULT_OK
		|| arguments_parse(args, argc, argv) != RESULT_OK)
	{
		return (RESULT_ERROR);
	}
	return (RESULT_OK);
}
