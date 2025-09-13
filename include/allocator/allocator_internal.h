/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:07:55 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/13 14:54:27 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_INTERNAL_H
# define ALLOCATOR_INTERNAL_H

# include "allocator.h"

t_arena			*allocator_arena_create(t_allocator *alc);
void			allocator_arena_destroy(t_arena *arena);

t_allocation	allocator_arena_alloc(t_arena *arena, size_t size);

t_slab_region	*allocator_slab_create(t_allocator *alc);
void			allocator_slab_destroy(t_slab_region *slab);

t_allocation	allocator_slab_alloc(t_slab_region *slab);
void			allocator_slab_free(t_allocation alloc);

#endif // ALLOCATOR_INTERNAL_H
