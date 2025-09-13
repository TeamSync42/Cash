/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 20:00:43 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/09/13 13:26:45 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_INTERNAL_H
# define HASH_TABLE_INTERNAL_H

# include "hash_table.h"

int32_t	hash_table_resize(t_hash_table *ht);

#endif // HASH_TABLE_INTERNAL_H
