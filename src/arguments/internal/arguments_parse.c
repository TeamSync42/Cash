/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:20:48 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/14 11:48:33 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments/arguments_internal.h"
#include "core/string/ft_string.h"

t_result	arguments_parse(t_arguments *args, const int argc, char **argv)
{
	int32_t	i;

	i = -1;
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
