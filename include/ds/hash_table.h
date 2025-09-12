/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:23:57 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/11 19:02:41 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include <stddef.h>
# include <stdint.h>

# define TOMBSTONE ((char *) -1)

typedef struct s_hash_entry {
	char	*command_name;
	char	*absolute_path;
	size_t	use_count;
}	t_hash_entry;

typedef struct s_hash_table {
	t_hash_entry	*table;
	size_t			table_size;
	size_t			item_count;
}	t_hash_table;

t_hash_table	*hash_table_create(void);
void			hash_table_destroy(t_hash_table *ht);
int32_t			hash_table_insert(t_hash_table *ht, const char *cmd,
					const char *path);
char			*hash_table_search(t_hash_table *ht, const char *cmd);
int32_t			hash_table_delete(t_hash_table *ht, const char *cmd);
void			hash_table_reset(t_hash_table *ht);

#endif // HASH_TABLE_H