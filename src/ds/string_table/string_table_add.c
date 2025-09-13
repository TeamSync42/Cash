/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_table_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 06:58:24 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/13 13:56:20 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "core/memory/ft_memory.h"
#include "core/string/ft_string.h"
#include "ds/string_table.h"

static size_t	initial_add(t_string_table *string_table, char ***new_storage)
{
	*new_storage = malloc(sizeof(char *) * INITIAL_STRING_TABLE_CAPACITY);
	if (!*new_storage)
		return (SIZE_MAX);
	string_table->strings = *new_storage;
	string_table->capacity = INITIAL_STRING_TABLE_CAPACITY;
	string_table->count = 0;
	return (0);
}

static size_t	add_with_realloc(t_string_table *string_table, char ***ns)
{
	size_t	new_capacity;

	if (string_table->capacity < INITIAL_STRING_TABLE_CAPACITY)
		new_capacity = INITIAL_STRING_TABLE_CAPACITY;
	else
		new_capacity = string_table->capacity * 2;
	*ns = (char **)realloc(string_table->strings,
			sizeof(char *) * new_capacity);
	if (!*ns)
		return (SIZE_MAX);
	string_table->strings = *ns;
	string_table->capacity = new_capacity;
	return (0);
}

size_t	string_table_add(t_string_table *string_table, const char *str)
{
	size_t	index;
	char	**new_storage;
	char	*dup;

	if (!string_table || !str)
		return (SIZE_MAX);
	if (!string_table->strings || string_table->capacity == 0)
	{
		if (initial_add(string_table, &new_storage) == SIZE_MAX)
			return (SIZE_MAX);
	}
	if (string_table->count >= string_table->capacity)
	{
		if (add_with_realloc(string_table, &new_storage) == SIZE_MAX)
			return (SIZE_MAX);
	}
	dup = ft_strdup(str);
	index = string_table->count;
	string_table->strings[index] = dup;
	string_table->count += 1;
	return (index);
}
