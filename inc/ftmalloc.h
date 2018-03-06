/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:47:45 by fjacquem          #+#    #+#             */
/*   Updated: 2018/03/06 09:55:32 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMALLOC_H
# define FTMALLOC_H
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <errno.h>
# include <stddef.h>
# include <pthread.h>
# include <unistd.h>
# define SIZE_T_MAX					(size_t)-1
# define FTMALLOC_DBG_MAXDIGIT		12
# define FTMALLOC_TINY				4096
# define FTMALLOC_SMALL				8192
# define FTMALLOC_BIG				65536
# define FTMALLOC_NBLOCKS			128
# define FTMALLOC_FILEID			"FT"
# define FTMALLOC_SHOW_WASTE		0x1
# define FTMALLOC_SHOW_AREA			0x2
# define FTMALLOC_SHOW_BLOCK		0x4
# define FTMALLOC_SHOW_CONTENT		0x8
# define FTMALLOC_SHOW_FREE			0x40
# define FTMALLOC_SHOW_RES_HARDPAGE	0x10
# define FTMALLOC_SHOW_RES_SOFTPAGE	0x20
# define FTMALLOC_SHOW_RES			0x30
# define FTMALLOC_SHOW_DATA			0xE
# define FTMALLOC_SHOW_ALL			0x3F
# define FTMALLOC_SHOW_ALL_FREE		0x7F
# define FTMALLOC_SHOW_RES_SELF		RUSAGE_SELF
# define FTMALLOC_SHOW_RES_CHILDREN	RUSAGE_CHILDREN
# define FTMALLOC_SHOW_RES_THREAD	RUSAGE_THREAD
# ifndef M_ARENA_MAX
#  define M_ARENA_MAX 1
# endif

typedef void			*(*memhook_t)(size_t, const void*(*));

extern					int			errno;
extern 					memhook_t g_malloc_hook;
extern 					memhook_t g_realloc_hook;
extern 					memhook_t g_free_hook;

typedef struct			s_blk
{
	intptr_t			addr;
	size_t				allocsize;
	int					freed:5;
	struct s_blk		*next;
}						t_blk;

typedef struct			s_area
{
	size_t				total_size;
	size_t				blksize;
	t_blk				*blocks;
	struct s_area		*next;
}						t_area;

typedef struct			s_alloc_opts
{
	int					prot;
	int					flags;
	int					fd;
	off_t				offset;
}						t_alloc_opts;

typedef struct			s_mcfg
{
	intptr_t			expected;
	t_alloc_opts		opts;
	t_area				*areas;
	size_t				psize;
	pthread_mutex_t		lock;
}						t_mcfg;

/*
**	External
*/
void					exit(int status);
int						atoi(const char *s);
void					ft_printdouble(double d, unsigned int precision);
void					ft_printhex(intptr_t v);
void					ft_printaddr(intptr_t v);
void					ft_printnum(intptr_t v);
void 					ft_printstr(const char *s);
void 					ft_bzero(const void *ptr, size_t size);
void 					ft_printshl(const char *s, intptr_t hex);

/*
**	Memory structure
*/
t_mcfg 					*mem_get_data(void);
void					mem_lock(t_mcfg *dat);
void					mem_unlock(t_mcfg *dat);

/*
**	Messurement
*/
size_t					mem_get_typesize(size_t allocsize);
int						mem_size_overflow(size_t psize, size_t typesize);
size_t					mem_get_total(size_t value, size_t add);

/*
**	Management
*/
intptr_t				mem_new(t_mcfg *cfg, size_t allocsize, size_t typesize);
void					mem_delete(t_mcfg *cfg, t_area **root);
int 					mem_is_overlap(t_mcfg *cfg);

/*
**	Search
*/
intptr_t 				mem_search_space(t_mcfg *dat, size_t allocsize, size_t typesize);

/*
**	Show
*/
void 					show_alloc_mem(void);

/*
**	Main functions
*/
void					*malloc(size_t size);
void					*realloc(void *addr, size_t size);
void					free(void *addr);
void 					*calloc(size_t nmemb, size_t size);

#endif
