/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_reset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:22:16 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/15 15:34:06 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ds/hash_table.h"

void	hash_table_reset(t_hash_table *ht)
{
	size_t	i;

	if (!ht)
		return ;
	i = 0;
	while (i < ht->table_size)
	{
		if (ht->table[i].cmd_name && ht->table[i].cmd_name != TOMBSTONE)
		{
			free(ht->table[i].cmd_name);
			free(ht->table[i].absolute_path);
		}
		ht->table[i].cmd_name = NULL;
		i++;
	}
	ht->item_count = 0;
	ht->tombstone_count = 0;
}
