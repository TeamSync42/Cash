/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:01:20 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/14 12:12:36 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments/arguments_internal.h"
#include "core/string/ft_string.h"
#include "io/ft_printf.h"

typedef struct s_assignation {
	t_argument		*arg;
	char			**argv;
	char			*value;
	int				*i;
	const int32_t	argc;
	char			padding[4];
}	t_assignation;

static void	extract_long_name_and_value(const char *arg,
			const char **long_name, char **value)
{
	*long_name = arg + 2;
	*value = ft_strchr(arg + 2, '=');
	if (*value)
		*(*value)++ = '\0';
}

static t_result	resolve_long_argument(const t_arguments *args,
			const char *long_name, const char *prog_name, t_argument **out_arg)
{
	t_argument	*arg;

	arg = arguments_find(args, long_name);
	if (!arg || !arg->long_name)
	{
		ft_printf("%s: --%s: invalid option\n", prog_name, long_name);
		return (RESULT_ERROR);
	}
	arg->is_set = 1;
	*out_arg = arg;
	return (RESULT_OK);
}

static t_result	assign_long_value(const t_assignation assignation)
{
	if (assignation.arg->has_value)
	{
		if (assignation.value)
			assignation.arg->value = assignation.value;
		else
		{
			if (*assignation.i + 1 >= assignation.argc)
			{
				ft_printf("Fatal: Missing value for argument\n");
				return (RESULT_ERROR);
			}
			assignation.arg->value = assignation.argv[++*assignation.i];
		}
		return (RESULT_OK);
	}
	if (assignation.value)
	{
		ft_printf("Warning: Argument does not accept a value\n");
		return (RESULT_ERROR);
	}
	return (RESULT_OK);
}

t_result	parse_long(const t_arguments *args, const int argc, char **argv,
				int *i)
{
	const char		*long_name;
	char			*value;
	t_argument		*arg;

	extract_long_name_and_value(argv[*i], &long_name, &value);
	if (resolve_long_argument(args, long_name, argv[0], &arg) != RESULT_OK)
		return (RESULT_ERROR);
	return (assign_long_value((t_assignation){
			.arg = arg,
			.argc = argc,
			.argv = argv,
			.i = i,
			.value = value
		})
	);
}
