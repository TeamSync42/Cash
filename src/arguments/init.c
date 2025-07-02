/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:06:01 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/02 13:09:24 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include "libft.h"

static void	parse_positional(t_arguments *args, const char *arg)
{
	ft_vector_push(&args->positional,
		ft_gen_val(TYPE_OTHER, (t_any){ .str = (char *)arg }));
}

t_result	parse(t_arguments *args, int argc, char **argv)
{
	int	i;

	i = -1;
	while (++i < argc)
	{
		if (argv[i][0] != '-')
			parse_positional(args, argv[i]);
	}
	return (RESULT_OK);
}

static int	get_size(int argc)
{
	if (argc > 8)
		return (argc / 2);
	return (4);
}

static	t_result	collect(t_result a, t_result b)
{

	if (a == RESULT_ERROR || b == RESULT_ERROR)
		return (RESULT_ERROR);
	return (RESULT_OK);
}

t_result	arguments_init(t_arguments *args, int argc, char **argv)
{
	const int	size = get_size(argc);
	t_result	result;

	result = RESULT_OK;
	collect(result, ft_vector_init(&args->positional, size));	
	collect(result, ft_vector_init(&args->options, size));
	collect(result, parse(args, argc, argv));
	return (result);
}

