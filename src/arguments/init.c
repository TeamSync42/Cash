/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:06:01 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/09 01:00:20 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include "libft.h"

static t_result	parse_positional(t_arguments *args, const char *arg)
{
	return (ft_vector_push(&args->positional,
			ft_gen_val(TYPE_OTHER, (t_any){.str = (char *)arg})));
}

static t_result	parse_short(t_arguments *args, int argc, char **argv, int *i)
{
	auto const char short_name = argv[*i][1];
	auto t_argument * arg = arguments_find_short(args, short_name);
	if (!arg || arg->short_name == '\0')
		return (ft_printf("%s: -%c: invalid option\n", args->name, short_name),
			RESULT_ERROR);
	arg->is_set = 1;
	if (arg->has_value)
	{
		if (argv[*i][2] == '=')
			arg->value = argv[*i] + 3;
		else if (argv[*i][2] == '\0')
		{
			if (*i + 1 >= argc)
				return (ft_printf("Fatal: Missing value for argument\n"),
					RESULT_ERROR);
			arg->value = argv[++*i];
		}
		else
			arg->value = argv[*i] + 2;
	}
	else if (argv[*i][2] != '\0')
		return (ft_printf("Fatal: Argument does not accept a value\n"),
			RESULT_ERROR);
	return (RESULT_OK);
}

static t_result	parse_long(t_arguments *args, int argc, char **argv, int *i)
{
	auto const char *long_name = argv[*i] + 2;
	auto char *value = ft_strchr(argv[*i] + 2, '=');
	if (value)
		*value++ = '\0';
	auto t_argument * arg = arguments_find(args, long_name);
	if (!arg || !arg->long_name)
		return (ft_printf("cash: --%s: invalid option\n", long_name),
			RESULT_ERROR);
	arg->is_set = 1;
	if (arg->has_value)
	{
		if (value)
			arg->value = value;
		else
		{
			if (*i + 1 >= argc)
				return (ft_printf("Fatal: Missing value for argument\n"),
					RESULT_ERROR);
			arg->value = argv[++*i];
		}
	}
	else if (value)
		return (ft_printf("Warning: Argument does not accept a value\n"),
			RESULT_ERROR);
	return (RESULT_OK);
}

static t_result	parse(t_arguments *args, int argc, char **argv)
{
	auto int i = -1;
	while (++i < argc)
	{
		if (argv[i][0] != '-')
		{
			if (parse_positional(args, argv[i]) != RESULT_OK)
				return (RESULT_ERROR);
		}
		else if (argv[i][1] != '-')
		{
			if (parse_short(args, argc, argv, &i) != RESULT_OK)
				return (RESULT_ERROR);
		}
		else
			if (parse_long(args, argc, argv, &i) != RESULT_OK)
				return (RESULT_ERROR);
	}
	return (RESULT_OK);
}

static int	get_size(int argc)
{
	if (argc > 8)
		return (argc / 2);
	return (4);
}

static inline t_result	collect(t_result a, t_result b)
{
	if (a == RESULT_ERROR || b == RESULT_ERROR)
		return (RESULT_ERROR);
	return (RESULT_OK);
}

#ifdef _DEBUG

static t_result	arguments_init_debug(t_arguments *args)
{
	auto t_result result = RESULT_OK;
	result = collect(result, arguments_add(args, "disassemble", 'd', 0));
	return (result);
}

#else

static t_result	arguments_init_debug(t_arguments *args)
{
	(void)args;
	return (RESULT_OK);
}

#endif

t_result	arguments_init(t_arguments *args, int argc, char **argv)
{
	auto const int size = get_size(argc);
	auto t_result result = RESULT_OK;
	args->name = argv[0];
	result = collect(result, ft_vector_init(&args->positional, (size_t)size));
	result = collect(result, ft_vector_init(&args->options, (size_t)size));
	if (result != RESULT_OK)
		return (RESULT_ERROR);
	result = collect(result, arguments_add(args, "posix", 0, 0));
	result = collect(result, arguments_add(args, "verbose", 'v', 0));
	result = collect(result, arguments_init_debug(args));
	result = collect(result, parse(args, argc, argv));
	return (result);
}

static void	arguments_option_free(size_t idx, t_value val)
{
	(void)idx;
	free(val.value.ptr);
}

void	arguments_destroy(t_arguments *args)
{
	ft_vector_foreach(&args->options, arguments_option_free);
	ft_vector_free(&args->options);
	ft_vector_free(&args->positional);
}
