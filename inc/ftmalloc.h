/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftmalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:47:45 by fjacquem          #+#    #+#             */
/*   Updated: 2018/03/22 09:25:32 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTMALLOC_H
# define FTMALLOC_H
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <errno.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <unistd.h>
# define FTMALLOC_MAGIC				"ALOCALOCALOCALOC"
# define SIZE_T_MAX					(size_t)-1
# define FTMALLOC_DBG_MAXDIGIT		12
# define FTMALLOC_TINY				1024
# define FTMALLOC_SMALL				1024 * 1024
# define FTMALLOC_NBLOCKS			256

typedef void			*(*memhook_t)(size_t, const void*(*));

extern					int			errno;
extern 					memhook_t g_malloc_hook;
extern 					memhook_t g_realloc_hook;
extern 					memhook_t g_free_hook;

typedef struct			s_blk
{
	intptr_t			addr;
	size_t				freed;
}						t_blk;

typedef struct			s_area
{
	char				magic[16];
	size_t				total_size;
	size_t				blksize;
	struct s_area		*next;
	t_blk				*blocks;
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
	size_t				total;
	struct rlimit		limits;
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
void					ft_printstr(const char *s);
void					ft_bzero(const void *ptr, size_t size);
void					ft_printshl(const char *s, intptr_t hex);
void					*ft_print_memory(const void *addr, size_t size);
void					*ft_memcpy(void *dst, const void *src, size_t len);
int						ft_memcmp(const void *s1, const void *s2, size_t n);

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
intptr_t				ft_mem_new(t_mcfg *cfg, size_t allocsize, size_t typesize);
void					ft_mem_delete(t_mcfg *cfg, t_area **root);
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
