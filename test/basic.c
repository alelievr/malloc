/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 20:19:08 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/11 01:19:32 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"

int		main(void)
{
	mallopt(M_VERBOSE, 1);
	printf("hello%s%i%s\n", " ", 42, " world !");
}
