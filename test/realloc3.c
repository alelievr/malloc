/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 23:40:15 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 23:50:41 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "malloc.h"

int		main(void)
{
	void		*ptr;
	const char	*str = "PATH=/Users/alelievr/brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/usr/texbin:/Users/alelievr/bin\n";

	ptr = malloc(127);
	strcpy(ptr, str);
	printf("str = %s\n", ptr);
	ptr = realloc(ptr, 20000);
	ptr = realloc(ptr, 130);
	ptr = realloc(ptr, 1000);
	ptr = realloc(ptr, 200000);
	printf("str = %s\n", ptr);
	free(ptr);
}
