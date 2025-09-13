/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:22:07 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/12 19:04:14 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collections/maps/hashmap/ft_hashmap.h"
#include "core/string/ft_string.h"
#include "ds/hash_table.h"

char	*hash_table_search(t_hash_table *ht, const char *cmd)
{
	size_t	i;

	if (!ht || !cmd)
		return (NULL);
	i = hashmap_djb2_hash(cmd) % ht->table_size;
	while (ht->table[i].cmd_name != NULL)
	{
		if (ht->table[i].cmd_name != TOMBSTONE
			&& ft_strcmp(ht->table[i].cmd_name, cmd) == 0)
		{
			ht->table[i].use_count++;
			return (ht->table[i].absolute_path);
		}
		i = (i + 1) % ht->table_size;
	}
	return (NULL);
}
