/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 02:06:23 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/13 21:40:57 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include <stdbool.h>
#include <stddef.h>

enum	E_MALLOC_INFO
{
	M_CHECK_CATCH =			0x1,
	M_CHECK_PRINT =			0x2,
	M_CHECK_ABORT =			0x4,
	M_CHECK_STACKTRACE =	0x8,
	M_CHECK_VERBOSE =		0x10,
	M_LIMIT_PAGES =			0x20,
	M_CATCH =				M_CHECK_CATCH,
	M_PRINT =				M_CHECK_PRINT,
	M_ABORT =				M_CHECK_ABORT,
	M_STACKTRACE =			M_CHECK_STACKTRACE,
	M_VERBOSE =				M_CHECK_VERBOSE,
};

extern void				*malloc(size_t size);
extern void				*realloc(void *ptr, size_t size);
extern void				*calloc(size_t count, size_t size);
extern void				*valloc(size_t size);

extern void				free(void *ptr);

extern void				mallopt(int option, int value);

extern size_t			malloc_page_size(void *ptr);
extern size_t			malloc_size(void *ptr);

extern bool				dump_all(void);

extern void				show_alloc_mem(void);
extern void				show_alloc_mem_ex(void);

#endif
