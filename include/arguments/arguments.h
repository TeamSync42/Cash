/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:01:08 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/14 10:24:51 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_H
# define ARGUMENTS_H

# include <stdbool.h>

# include "collections/vectors/vector.h"

typedef struct s_argument
{
	const char	*long_name;
	char		*value;
	char		short_name;
	bool		is_set;
	bool		has_value;
	char		padding[5];
}	t_argument;

typedef struct s_arguments
{
	char		*name;
	t_vector	options;
	t_vector	positional;
}	t_arguments;

t_result	arguments_init(t_arguments *args, int argc, char **argv);
void		arguments_destroy(const t_arguments *args);
t_argument	*arguments_find(const t_arguments *args, const char *name);
t_argument	*arguments_find_short(const t_arguments *args, char name);
t_result	arguments_add(t_arguments *args, const char *long_name,
				char short_name, bool has_value);
char		*arguments_get(const t_arguments *args, const char *name);
bool		arguments_is_set(const t_arguments *args, const char *name);

#endif // ARGUMENTS_H
