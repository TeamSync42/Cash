/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:22:12 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/15 15:33:49 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "collections/maps/hashmap/ft_hashmap.h"
#include "core/string/ft_string.h"
#include "ds/hash_table.h"

int32_t	hash_table_delete(t_hash_table *ht, const char *cmd)
{
	size_t	i;

	if (!ht || !cmd)
		return (EINVAL);
	i = hashmap_djb2_hash(cmd) % ht->table_size;
	while (ht->table[i].cmd_name != NULL)
	{
		if (ht->table[i].cmd_name != TOMBSTONE
			&& ft_strcmp(ht->table[i].cmd_name, cmd) == 0)
		{
			free(ht->table[i].cmd_name);
			free(ht->table[i].absolute_path);
			ht->table[i].cmd_name = TOMBSTONE;
			if (ht->item_count > 0)
				ht->item_count--;
			ht->tombstone_count++;
			return (0);
		}
		i = (i + 1) % ht->table_size;
	}
	return (ENOENT);
}
