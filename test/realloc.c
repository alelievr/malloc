/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 22:41:20 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 23:07:49 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <string.h>

int		main(void)
{
	void	*p;

	mallopt(M_VERBOSE, 1);
	p = malloc(1000 * 1000 * 2);
	strcpy(p, "hello !\n");
	printf("%s", p);
	malloc(1000 * 1000 * 16);
	p = realloc(p, 1000 * 1000 * 30);
	printf("%s", p);
}
