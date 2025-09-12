/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_resize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:01:42 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/12 20:04:50 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collections/maps/hashmap/ft_hashmap.h"
#include "core/memory/ft_memory.h"
#include "ds/hash_table_internal.h"

static void	rehash_all_entries(const t_hash_table *ht, t_hash_entry *new_table,
				const size_t new_size)
{
	size_t		i;
	uint64_t	new_hash;
	size_t		j;

	i = 0;
	while (i < ht->table_size)
	{
		if (ht->table[i].cmd_name && ht->table[i].cmd_name != TOMBSTONE)
		{
			new_hash = hashmap_djb2_hash(ht->table[i].cmd_name);
			j = new_hash % new_size;
			while (new_table[j].cmd_name != NULL)
				j = (j + 1) % new_size;
			new_table[j] = ht->table[i];
		}
		i++;
	}
}

int32_t	hash_table_resize(t_hash_table *ht)
{
	size_t			new_size;
	t_hash_entry	*new_table;

	new_size = ht->table_size * 2;
	new_table = ft_calloc(new_size, sizeof(t_hash_entry));
	if (!new_table)
		return (ENOMEM);
	rehash_all_entries(ht, new_table, new_size);
	free(ht->table);
	ht->table = new_table;
	ht->table_size = new_size;
	return (0);
}
