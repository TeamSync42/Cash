/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_insert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:22:01 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/12 20:10:32 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collections/maps/hashmap/ft_hashmap.h"
#include "core/string/ft_string.h"
#include "ds/hash_table.h"
#include "ds/hash_table_internal.h"

#define LOAD_FACTOR_THRESHOLD 0.6

static int32_t	ensure_capacity(t_hash_table *ht)
{
	int32_t	status;

	if ((double)(ht->item_count + 1)
		/ (double)ht->table_size > LOAD_FACTOR_THRESHOLD)
	{
		status = hash_table_resize(ht);
		if (status != 0)
			return (status);
	}
	return (0);
}

static int32_t	insert_new_entry(t_hash_table *ht, const size_t idx,
				const char *cmd, const char *path)
{
	char	*dup_cmd;
	char	*dup_path;

	dup_cmd = ft_strdup(cmd);
	if (!dup_cmd)
		return (ENOMEM);
	dup_path = ft_strdup(path);
	if (!dup_path)
	{
		free(dup_cmd);
		return (ENOMEM);
	}
	ht->table[idx].cmd_name = dup_cmd;
	ht->table[idx].absolute_path = dup_path;
	ht->table[idx].use_count = 1;
	ht->item_count++;
	return (0);
}

static int32_t	update_existing_entry(const t_hash_table *ht, const size_t idx,
				const char *path)
{
	char	*dup_path;

	dup_path = ft_strdup(path);
	if (!dup_path)
		return (ENOMEM);
	free(ht->table[idx].absolute_path);
	ht->table[idx].absolute_path = dup_path;
	ht->table[idx].use_count = 1;
	return (0);
}

static void	find_slot_or_existing(const t_hash_table *ht, const char *cmd,
				size_t *existing_idx, size_t *insert_idx)
{
	size_t	i;
	size_t	first_tomb;

	*existing_idx = (size_t)-1;
	*insert_idx = (size_t)-1;
	i = hashmap_djb2_hash(cmd) % ht->table_size;
	first_tomb = (size_t)-1;
	while (ht->table[i].cmd_name != NULL)
	{
		if (ht->table[i].cmd_name == TOMBSTONE
			&& first_tomb == (size_t) - 1)
			first_tomb = i;
		else if (ft_strcmp(ht->table[i].cmd_name, cmd) == 0)
		{
			*existing_idx = i;
			return ;
		}
		i = (i + 1) % ht->table_size;
	}
	if (first_tomb != (size_t)-1)
		*insert_idx = first_tomb;
	else
		*insert_idx = i;
}

int32_t	hash_table_insert(t_hash_table *ht, const char *cmd, const char *path)
{
	int32_t	status;
	size_t	existing;
	size_t	insert;

	if (!ht || !cmd || !path)
		return (EINVAL);
	status = ensure_capacity(ht);
	if (status != 0)
		return (status);
	find_slot_or_existing(ht, cmd, &existing, &insert);
	if (existing != (size_t)-1)
		return (update_existing_entry(ht, existing, path));
	return (insert_new_entry(ht, insert, cmd, path));
}
