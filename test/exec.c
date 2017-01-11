/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 23:28:18 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/10 23:32:39 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <stdio.h>

int		main(void)
{
	printf("executing %s binary ...\n", "ls");

	char	*bin[] = {"ls", "-laR", NULL};
	char	*env[] = {"DYLD_INSERT_LIBRARIES=/Users/alelievr/c/ft_malloc/libft_malloc_x86_64_Darwin.so", "DYLD_FORCE_FLAT_NAMESPACE=1"};

	execve("/bin/ls", bin, env);
}
