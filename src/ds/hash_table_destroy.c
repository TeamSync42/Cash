/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:21:53 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/13 13:22:25 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ds/hash_table.h"

void	hash_table_destroy(t_hash_table *ht)
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
		i++;
	}
	free(ht->table);
}
