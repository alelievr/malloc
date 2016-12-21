/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_page.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 13:50:13 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/21 15:19:28 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	alloc_start_page(t_page *p, t_alloc *free_block, size_t size)
{
	t_alloc		*tmp;

	free_block->start = p->start;
	free_block->end = p->start + size;
	if (p->alloc == NULL)
		p->alloc = free_block;
	else
	{
		tmp = p->alloc;
		p->alloc = free_block;
		p->alloc->next = tmp;
	}
}

static void	alloc_at_page(t_alloc *prev, t_alloc *free_block, size_t size)
{
	t_alloc		*tmp;

	free_block->start = prev->end;
	free_block->end = prev->end + size;
	tmp = prev->next;
	prev->next = free_block;
	free_block->next = tmp;
}

static void	update_max_free_bytes_block(t_page *p)
{
	long		max;
	t_alloc		*alloc;

	alloc = p->alloc;
	max = 0;
	while (alloc->next)
	{
		if (alloc->next->start - alloc->end > max)
			max = alloc->next->start - alloc->end;
		alloc = alloc->next;
	}
	if (p->end - alloc->end > max)
		max = p->end - alloc->end;
	p->max_free_bytes_block = max;
}

void		*page_alloc(t_page *p, size_t size)
{
	t_alloc		*free_alloc_block;
	t_alloc		*alloc;
	int			i;

	if (FOR(i = 0, i < MAX_ALLOCS_IN_PAGE, i++))
		if (p->_allocs_buff[i].start == NULL)
		{
			free_alloc_block = p->_allocs_buff + i;
			break ;
		}
	alloc = p->alloc;
	//check if enouth space between strt of page and first allocated block:
	if (alloc == NULL || alloc->start - p->start > (long)size)
		alloc_start_page(p, free_alloc_block, size);
	while (alloc->next)
	{
		if (alloc->next->start - alloc->end > (long)size)
			alloc_at_page(alloc, free_alloc_block, size);
		alloc = alloc->next;
	}
	alloc_at_page(alloc, free_alloc_block, size);
	update_max_free_bytes_block(p);
	return free_alloc_block->start;
}
