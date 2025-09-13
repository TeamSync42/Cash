/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:21:45 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/13 14:19:54 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/memory/ft_memory.h"
#include "ds/hash_table.h"

#define HASH_TABLE_INIT_SIZE 101

int32_t	hash_table_init(t_hash_table *ht)
{
	ht->table_size = HASH_TABLE_INIT_SIZE;
	ht->item_count = 0;
	ht->table = ft_calloc(ht->table_size, sizeof(t_hash_entry));
	if (!ht->table)
		return (ENOMEM);
	return (0);
}
