/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:07:55 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/13 10:08:52 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_INTERNAL_H
# define ALLOCATOR_INTERNAL_H

# include "allocator.h"

t_arena			*allocator_arena_new(t_allocator *alc, size_t capacity);
t_slab_region	*allocator_slab_new(t_allocator *allocator, size_t block_size,
					size_t num_blocks);
t_allocation	allocator_slab_alloc(t_slab_region *slab);
void			allocator_slab_free(t_allocation alloc);

#endif
