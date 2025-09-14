/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_short.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 11:48:17 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/14 12:01:59 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments/arguments_internal.h"
#include "io/ft_printf.h"

static t_result	parse_short_value(t_argument *arg, const int argc,
			char **argv, int *i)
{
	if (argv[*i][2] == '=')
	{
		arg->value = argv[*i] + 3;
		return (RESULT_OK);
	}
	if (argv[*i][2] == '\0')
	{
		if (*i + 1 >= argc)
		{
			ft_printf("Fatal: Missing value for argument\n");
			return (RESULT_ERROR);
		}
		*i = *i + 1;
		arg->value = argv[*i];
		return (RESULT_OK);
	}
	arg->value = argv[*i] + 2;
	return (RESULT_OK);
}

t_result	parse_short(const t_arguments *args, const int argc, char **argv,
			int *i)
{
	const char	short_name = argv[*i][1];
	t_argument	*arg;

	arg = arguments_find_short(args, short_name);
	if (!arg || arg->short_name == '\0')
	{
		ft_printf("%s: -%c: invalid option\n", args->name, short_name);
		return (RESULT_ERROR);
	}
	arg->is_set = 1;
	if (arg->has_value)
		return (parse_short_value(arg, argc, argv, i));
	if (argv[*i][2] != '\0')
	{
		ft_printf("Fatal: Argument does not accept a value\n");
		return (RESULT_ERROR);
	}
	return (RESULT_OK);
}
