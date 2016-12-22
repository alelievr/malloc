/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 02:55:01 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/22 02:08:15 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
#include <stdio.h>

int		main(void)
{
	printf("sizeof(page): %lu\n", sizeof(t_page));
	printf("sizeof(heap): %lu\n", sizeof(t_heap));
	mallopt(M_VERBOSE, true);
	ft_alloc(NULL, 10);
	ft_alloc(NULL, 10);
	ft_alloc(NULL, 10);
	dump_all();
	return (0);
}
