/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 02:55:01 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/21 01:21:01 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>

int		main(void)
{
	printf("sizeof(page): %lu\n", sizeof(t_page));
	printf("sizeof(heap): %lu\n", sizeof(t_heap));
	return (0);
}
