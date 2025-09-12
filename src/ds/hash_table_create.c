/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:21:45 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/12 18:58:42 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/memory/ft_memory.h"
#include "ds/hash_table.h"

#define HASH_TABLE_INIT_SIZE 101

t_hash_table	*hash_table_create(void)
{
	t_hash_table	*ht;

	ht = malloc(sizeof(t_hash_table));
	if (!ht)
		return (NULL);
	ht->table_size = HASH_TABLE_INIT_SIZE;
	ht->item_count = 0;
	ht->table = ft_calloc(ht->table_size, sizeof(t_hash_entry));
	if (!ht->table)
	{
		free(ht);
		return (NULL);
	}
	return (ht);
}
