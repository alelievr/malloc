/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 02:58:16 by alelievr          #+#    #+#             */
/*   Updated: 2017/01/11 02:31:51 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/mman.h>
# include "libft.h"
# include "malloc.h"

//# define DEBUG

# define MIN_ALLOC_SIZE		0x10
# define MAX_ALLOCS_IN_PAGE	128
# define MAX_PAGES_PER_HEAP	128

# define M_ERROR_COLOR				"\033[38;5;196m"
# define M_FREED_BYTE_COLOR			"\033[38;5;226m"
# define M_UNALLOCATED_BYTE_COLOR	"\033[38;5;245m"
# define M_ALLOCATED_BYTE_COLOR		"\033[38;5;154m"
# define M_DEBUG_COLOR				"\033[38;5;231m"
# define M_CLEAR_COLOR				"\033[0m"

# ifdef DEBUG
#  undef DEBUG
#  define DEBUG(x, args...) ft_printf(M_DEBUG_COLOR x M_CLEAR_COLOR, ##args);
# else
#  define DEBUG(x, args...)
# endif

/*
**	TINY = getpagesize() / 128 (max number of allocs in a page) 
**	SMALL = getpagesize() / 128 * 8
**	LARGE = custom size > at 256
*/

enum	E_MALLOC_SIZE
{
	M_TINY = 32,
	M_SMALL = 128,
	M_LARGE = -1,
	M_TINY_PAGE = M_TINY * MAX_ALLOCS_IN_PAGE,
	M_SMALL_PAGE = M_SMALL * MAX_ALLOCS_IN_PAGE,
	M_LARGE_PAGE = -1
};

enum	E_MALLOC_LIMITS
{
	M_UNLIMITED = -1,
	M_MAX = -2,
	M_MIN = -3,
};

# define M_OPT_PRINT		(get_malloc_info()->debug_flag & 1 << M_CHECK_PRINT)
# define M_OPT_IGNORE		(get_malloc_info()->debug_flag & 1 << M_CHECK_IGNORE)
# define M_OPT_ABORT		(get_malloc_info()->debug_flag & 1 << M_CHECK_ABORT)
# define M_OPT_STACKTRACE	(get_malloc_info()->debug_flag & 1 << M_CHECK_STACKTRACE)
# define M_OPT_VERBOSE		(get_malloc_info()->debug_flag & 1 << M_CHECK_VERBOSE)
# define ERR(x, args...)	ft_dprintf(2, x, ##args);

# define LOCK		pthread_mutex_lock(&g_malloc_mutex);
# define UNLOCK		pthread_mutex_unlock(&g_malloc_mutex);
# define NIL		NULL

typedef struct		s_alloc
{
	void			*start;
	void			*end;
	struct s_alloc	*next;
}					t_alloc;

typedef struct		s_page
{
	int			page_type;
	int			max_free_bytes_block;
	t_alloc		_allocs_buff[MAX_ALLOCS_IN_PAGE];
	t_alloc		*alloc;
	void		*start;
	void		*_page_alloc_ptr;
	void		*end;
	size_t		total_alloc_size;
}					t_page;

typedef struct		s_heap
{
	t_page			*pages_chunk[MAX_PAGES_PER_HEAP];
	struct s_heap	*next;
	int				free_pages_number;
	short			allocated;
	short			index;
}					t_heap;

typedef struct		s_malloc_info
{
	int		debug_flag;
	int		max_pages;
	size_t	max_page_size;
}					t_malloc_info;

typedef bool (*t_page_callback)(t_page *p, t_heap *heap, int index);
typedef bool (*t_heap_callback)(t_heap *h);

extern void					abort(void);

extern pthread_mutex_t		g_malloc_mutex;

/*
**	Pages functions:
*/
t_page				*new_page(size_t size, bool locked);
void				free_page(t_page *p);
bool				foreach_pages(t_page_callback f);

/*
**	Heap functions:
*/
t_heap				*alloc_and_append_new_heap(void);
t_heap				*get_heap(void) __attribute__((constructor));
bool				foreach_heap(t_heap_callback f, bool failsafe);
bool				foreach_allocated_heap(t_heap_callback f);

/*
**	Option functons:
*/
t_malloc_info		*get_malloc_info(void);
void				mallopt(int flag, int value);

/*
**	Utils functions:
*/
void				*mmap_wrapper(void *ptr, size_t size);
void				munmap_wrapper(void *addr, size_t size);
int					size_to_type(size_t size);
char				*type_to_text(int type);
void				stacktrace(void);
void				add_new_page_to_heap(t_page *p);

bool				find_page(void *ptr, t_heap **f_heap, int *f_index);
void				update_max_free_bytes_block(t_page *p);
t_alloc				*find_alloc(t_page *p, void *ptr);
void				free_alloc(t_page *p, t_alloc *a);

/*
**	Dump and print functions:
*/
bool				dump_all(void);
bool				dump_heap(t_heap *h);
bool				dump_page(t_page *p);

/*
**	Virtual memory management functions:
*/
void				*alloc_page(t_page *p, size_t size);
void				*ft_alloc(void *ptr, size_t size);
void				*ft_realloc(void *ptr, size_t size);
t_page				*large_alloc(size_t size, void *data, size_t dsize);
void				ft_free(void *ptr);

#endif
