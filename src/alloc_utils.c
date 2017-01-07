/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 01:06:12 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/07 20:56:38 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"

bool		find_page(void *ptr, t_heap **h, int *i)
{
	(void)ptr;
	(void)h;
	(void)i;
	return false;
}

t_alloc		*find_alloc(t_page *p, void *ptr)
{
	(void)p;
	(void)ptr;
	return NULL;
}

void		free_alloc(t_page *p, t_alloc *a)
{
	(void)p;
	(void)a;
}
