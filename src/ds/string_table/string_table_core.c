/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_table_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 07:00:37 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/13 14:18:44 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

#include "core/memory/ft_memory.h"
#include "ds/string_table.h"

static int32_t	last_check(const size_t new_capacity, const size_t cap,
			size_t *out)
{
	if (new_capacity <= cap || new_capacity > SIZE_MAX / sizeof(char *))
	{
		errno = ENOMEM;
		return (0);
	}
	*out = new_capacity;
	return (1);
}

static int32_t	compute_new_capacity(const t_string_table *string_table,
			size_t *out_new_capacity)
{
	size_t	cap;
	size_t	req;
	size_t	new_capacity;

	cap = string_table->capacity;
	if (string_table->count == SIZE_MAX)
	{
		errno = ENOMEM;
		return (0);
	}
	req = string_table->count + 1;
	if (cap == 0)
		new_capacity = INITIAL_STRING_TABLE_CAPACITY;
	else if (cap >= SIZE_MAX / 2)
		new_capacity = SIZE_MAX;
	else
		new_capacity = cap * 2;
	if (new_capacity < req)
		new_capacity = req;
	return (last_check(new_capacity, cap, out_new_capacity));
}

static int32_t	string_table_grow(t_string_table *string_table)
{
	size_t	new_capacity;
	char	**new_storage;
	size_t	i;

	if (!compute_new_capacity(string_table, &new_capacity))
		return (0);
	new_storage = realloc(string_table->strings, new_capacity * sizeof(char *));
	if (!new_storage)
	{
		errno = ENOMEM;
		return (0);
	}
	i = string_table->capacity;
	while (i < new_capacity)
		new_storage[i++] = NULL;
	string_table->strings = new_storage;
	string_table->capacity = new_capacity;
	return (1);
}

int32_t	string_table_init(t_string_table *string_table)
{
	if (!string_table)
	{
		errno = EINVAL;
		return (0);
	}
	string_table->strings = NULL;
	string_table->count = 0;
	string_table->capacity = 0;
	if (!string_table_grow(string_table))
		return (0);
	return (1);
}

void	string_table_cleanup(t_string_table *string_table)
{
	size_t	i;

	if (!string_table)
		return ;
	if (string_table->strings)
	{
		i = 0;
		while (i < string_table->count)
		{
			free(string_table->strings[i]);
			string_table->strings[i] = NULL;
			++i;
		}
		free(string_table->strings);
	}
	string_table->strings = NULL;
	string_table->count = 0;
	string_table->capacity = 0;
}
