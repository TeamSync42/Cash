/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:01:08 by smamalig          #+#    #+#             */
/*   Updated: 2025/09/14 14:05:12 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/allocator.h"
#include "allocator/allocator_internal.h"
#include <stdlib.h>

void	allocator_free(t_allocator *alc, t_allocation alloc)
{
	(void)alc;
	if (alloc.kind == ALLOC_ARENA)
		return ;
	if (alloc.kind == ALLOC_ALLOC)
	{
		free(alloc.data);
		return ;
	}
	if (alloc.kind == ALLOC_SLAB)
	{
		allocator_slab_free(alloc);
		return ;
	}
}
