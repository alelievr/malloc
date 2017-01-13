/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 02:55:01 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 20:44:51 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
#include <stdio.h>

int		main(void)
{
	void	*p1;//, *p2, *p3;

	ft_printf("sizeof(page): %lu\n", sizeof(t_page));
	ft_printf("sizeof(heap): %lu\n", sizeof(t_heap));
	mallopt(M_VERBOSE, true);
	p1 = ft_alloc(NULL, 10);
	ft_alloc(p1, 0x200);
	printf("%s\n", p1);
	/*p2 = ft_alloc(NULL, 10);
	p3 = ft_alloc(NULL, 10);
	p3 = ft_alloc(NULL, 512);*/
	ft_free(ft_alloc(NULL, 10));
	ft_free(ft_alloc(NULL, 10));
	ft_free(ft_alloc(NULL, 10));
	ft_free(ft_alloc(NULL, 10));
	dump_all();
	//ft_free(p2);
//	dump_all();
	return (0);
}
