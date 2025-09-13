/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:10:44 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/13 16:55:46 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include <stdlib.h>

t_allocation	allocator_alloc(t_allocator *alc, size_t size, t_arena_id id)
{
	t_allocation	alloc;
	t_arena			*arena;

	if (id != 0)
	{
		arena = allocator_arena_find(alc, id);
		return (allocator_arena_alloc(arena, size));
	}
	if (size <= MAX_SLAB_SIZE)
		return (allocator_slab_alloc(alc, size));
	alloc.size = size;
	alloc.kind = ALLOC_ALLOC;
	alloc.data = malloc(size);
	alloc.parent_id = 0;
	alloc.region = NULL;
	return (alloc);
}
