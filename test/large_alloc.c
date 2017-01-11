/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 22:57:58 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/10 23:24:31 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <string.h>

#define SIZE	100000

int		main(void)
{
	mallopt(M_VERBOSE, 1);
	void	*p = malloc(SIZE);
	memset(p, 'A', SIZE);
	dump_all();
	realloc(p, 10);
	dump_all();
	free(p);
	dump_all();
}
