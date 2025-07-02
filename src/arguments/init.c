/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:06:01 by smamalig          #+#    #+#             */
/*   Updated: 2025/07/02 15:34:09 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include "libft.h"

static void	parse_positional(t_arguments *args, const char *arg)
{
	ft_vector_push(&args->positional,
		ft_gen_val(TYPE_OTHER, (t_any){ .str = (char *)arg }));
}

static void	parse_short(t_arguments *args, int argc, char **argv, int *i)
{
	const char short_name = argv[*i][1];
	t_argument *arg = arguments_find_short(args, short_name);
	if (!arg || arg->short_name == '\0')
	{
		ft_printf("Warning: Unknown argument\n");
		return ;
	}
	arg->is_set = 1;
	if (arg->has_value) {
		if (argv[*i][2] == '=') {
			arg->value = argv[*i] + 3;
		} else if (argv[*i][2] == '\0') {
			if (*i + 1 >= argc) {
				ft_printf("Fatal: Missing value for argument\n");
				exit(EXIT_FAILURE);
				return ;
			}
			arg->value = argv[++*i];
		}
		else {
			arg->value = argv[*i] + 2;
		}
	} else if (argv[*i][2] != '\0') {
		ft_printf("Fatal: Argument does not accept a value\n");
		exit(EXIT_FAILURE);
	}
}

static void parse_long(t_arguments *args, int argc, char **argv, int *i)
{
	const char	*long_name = argv[*i] + 2;
	char		*value = ft_strchr(argv[*i] + 2, '=');
	if (value) {
		*value++ = '\0';
	}
	t_argument *arg = arguments_find(args, long_name);
	if (!arg || !arg->long_name)
	{
		ft_printf("Warning: Unknown argument\n");
		return ;
	}
	arg->is_set = 1;
	if (arg->has_value)
	{
		if (value) {
			arg->value = value;
		} else {
			if (*i + 1 >= argc)
			{
				ft_printf("Fatal: Missing value for argument\n");
				exit(EXIT_FAILURE);
			}
			arg->value = argv[++*i];
		}
	}
	else if (value)
	{
		ft_printf("Warning: Argument does not accept a value\n");
	}
}

t_result	parse(t_arguments *args, int argc, char **argv)
{
	int	i;

	i = -1;
	while (++i < argc)
	{
		if (argv[i][0] != '-')
			parse_positional(args, argv[i]);
		else if (argv[i][1] != '-')
			parse_short(args, argc, argv, &i);
		else
			parse_long(args, argc, argv, &i);
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
	arguments_add(args, "posix", 0, 0);
	arguments_add(args, "verbose", 'v', 0);
	collect(result, parse(args, argc, argv));
	return (result);
}

