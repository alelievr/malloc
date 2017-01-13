/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 18:23:47 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/12 20:17:47 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <string.h>
#include <stdio.h>

int		main(void)
{
	char	*ret;

	mallopt(M_VERBOSE, 1);
	ret = calloc(1, 10000);
	strcpy(ret, "olol\n");
	printf("%s", ret);
}
