/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 00:56:30 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/11 00:59:09 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"

int		main(void)
{
	mallopt(M_VERBOSE, 1);
	for (int i = 0; i < 200; i++)
		free(realloc(malloc(20), 30));
	dump_all();
}
