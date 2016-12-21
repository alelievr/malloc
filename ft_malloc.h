/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 02:58:16 by alelievr          #+#    #+#             */
/*   Updated: 2016/12/21 02:26:48 by alelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/mman.h>
# include "libft.h"

# define MIN_ALLOC_SIZE		0x10
# define MAX_ALLOCS_IN_PAGE	128
# define MAX_PAGES_PER_HEAP	128

enum	E_MALLOC_COLORS
{
	M_EORROR_COLOR = 196,
	M_FREED_BYTE_COLOR = 226,
	M_UNALLOCATED_BYTE_COLOR = 245,
	M_ALLOCATED_BYTE_COLOR = 154,
};

enum	E_MALLOC_INFO
{
	M_CHECK_IGNORE = 0x1,
	M_CHECK_PRINT = 0x2,
	M_CHECK_ABORT = 0x4,
	M_CHECK_STACKTRACE = 0x8,
	M_LIMIT_PAGES = 0x10,
};

/*
**	TINY = getpagesize() / 128 (max number of allocs in a page) 
**	SMALL = getpagesize() / 128 * 8
**	LARGE = custom size > at 256
*/

enum	E_MALLOC_SIZE
{
	M_TINY = 32,
	M_SMALL = 256,
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

# define DEBUG_PRINT (get_malloc_info()->debug_flag & 1 << M_CHECK_PRINT)
# define DEBUG_IGNORE (get_malloc_info()->debug_flag & 1 << M_CHECK_IGNORE)
# define DEBUG_ABORT (get_malloc_info()->debug_flag & 1 << M_CHECK_ABORT)
# define DEBUG_STACKTRACE (get_malloc_info()->debug_flag & 1 << M_CHECK_STACKTRACE)
# define ERR(x) write(2, x, sizeof(x));

# define LOCK		pthread_mutex_lock(&g_malloc_mutex);
# define UNLOCK		pthread_mutex_unlock(&g_malloc_mutex);
# define NIL		NULL
# define ALLOC_PAGE(x) mmap(NIL,x,PROT_READ|PROT_WRITE,MAP_ANON|MAP_PRIVATE,0,0)

typedef struct		s_alloc
{
	void	*start;
	void	*end;
	struct s_alloc	*next;
}					t_alloc;

typedef struct		s_page
{
	int			page_type;
	int			max_free_bytes_block;
	t_alloc		_allocs_buff[MAX_ALLOCS_IN_PAGE];
	t_alloc		*alloc;
	void		*start;
	void		*end;
	size_t		total_alloc_size;
}					t_page;

typedef struct		s_heap
{
	t_page			*pages_chunk[MAX_PAGES_PER_HEAP];
	struct s_heap	*next;
	int				free_pages_number;
	int				allocated;
}					t_heap;

typedef struct		s_malloc_info
{
	int		debug_flag;
	int		max_pages;
	size_t	max_page_size;
}					t_malloc_info;

typedef bool (*t_page_callback)(t_page *p, t_heap *heap, int index);
typedef bool (*t_heap_callback)(t_heap *h);

extern pthread_mutex_t		g_malloc_mutex;

/*
**	Pages functions:
*/
t_page				*new_page(size_t size);
void				delete_page(t_page *p);
bool				foreach_pages(t_page_callback f);

/*
**	Heap functions:
*/
t_heap				*alloc_and_append_new_heap(void);
t_heap				*get_heap(void) __attribute__((constructor));
bool				foreach_heap(t_heap_callback f, bool failsafe);

/*
**	Option functons:
*/
t_malloc_info		*get_malloc_info(void);


/*
**	Utils functions:
*/
void			*mmap_wrapper(size_t size);
void			munmap_wrapper(void *addr, size_t size);

/*typedef struct	s_allocated
{
	void	*addr;
	size_t	size;
}				t_allocated;

typedef struct	s_allocated_list
{
	t_allocated				allocs[128];
	struct s_allocated_list	*next;
}				t_alloc_list;

typedef struct	s_page
{
	void			*addr;
	size_t			size;
	t_alloc_list	alloc;
	struct s_page	*next;
}				t_page;


typedef struct	s_heap
{
	t_page			pages[256];
	t_alloc_list	fatalloc;
	t_malloc_info	infos;
}				t_heap;

t_heap			*get_heap(void);
t_malloc_info	*get_malloc_info(void);
void			*fatalloc(size_t size);

void			hexdump_page(t_page *p);
void			hexdump_allocated(t_allocated *a);

int				find_fatallocated_addr(void *ptr);
int				find_allocated_addr(void *ptr);
void			free_fatalloc(int index);
void			free_alloc(int index);*/

#endif
