#ifndef FTMALLOC_H
# define FTMALLOC_H
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <stddef.h>
# ifdef NO_MT_SAFE
# else
#  include <pthread.h>
# endif
# include <unistd.h>
# define SIZE_T_MAX					(size_t)-1
# define FTMALLOC_DBG_MAXDIGIT		12
# define FTMALLOC_TINY				128
# define FTMALLOC_SMALL				1024
# define FTMALLOC_BIG				8192
# define FTMALLOC_FACTOR			1
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

	typedef struct		s_blk
	{
		void			*addr;
		size_t			allocsize;
		int				freed;
		struct s_blk	*next;
	}					t_blk;

	typedef struct		s_area
	{
		size_t			blktype;
		size_t			nblk;
		size_t			psize;
		t_blk			*blocks;
		struct s_area	*next;
	}					t_area;

	typedef struct		s_alloc_opts
	{
		int				prot;
		int				flags;
		int				fd;
		off_t			offset;
	}					t_alloc_opts;

	typedef struct		s_mcfg
	{
		t_alloc_opts	opts;
		t_area			*areas;
		size_t			arenamax;
		size_t			psize;
		void			*(*malloc_hook)(size_t, const void*(*));
		void			*(*realloc_hook)(size_t, const void*(*));
		void			*(*free_hook)(size_t, const void*(*));
# ifdef NO_MT_SAFE
# else
		pthread_mutex_t	lock;
# endif
	}					t_mcfg;

void					exit(int status);
int						atoi(const char *s);

void					mem_clear_space(t_mcfg *dat, void *addr);
void					mem_areas_clear(t_area **a);

void					mem_lock(t_mcfg *dat);
void					mem_unlock(t_mcfg *dat);

void					*mem_get_free_space(t_mcfg *dat, size_t size, size_t blktype);
void					*mem_reset_space(t_mcfg *dat, void *addr, size_t size, size_t blktype);

void					mem_numofdigit(intptr_t v, unsigned int base, size_t *n);
void					mem_printaddr(intptr_t v, int max, int show_x);
void					mem_printnum(intptr_t v);

size_t					mem_get_pagesize(size_t blksize);
size_t					mem_get_blksize(size_t allocsize);
size_t					mem_get_nblk(size_t blksize, size_t psize);
size_t					mem_correct_factor(size_t psize, size_t allocsize);

void					show_alloc_ex(void);
void					show_alloc_mem_ex(void);
void					show_alloc_dbg(unsigned int flag, int who);

t_mcfg					*mem_get_data(void);

void					mem_area_set(t_area *a, size_t allocsize, size_t blksize, size_t mapsize);
t_area					*mem_area_init(t_mcfg *dat, size_t psize, size_t allocsize, void *expected_addr);
int						mem_area_reset(t_area *a, size_t allocsize, size_t blksize);

double					mem_get_waste(void);
size_t					mem_get_unused(t_area *a);
size_t					mem_get_usage(t_area *a);
size_t					mem_get_page_usage(t_area *a);
size_t					mem_get_block_usage(t_area *a);

void					*malloc(size_t size);
void					*calloc(size_t nmenb, size_t size);
void					*realloc(void *addr, size_t size);
void					*reallocarray(void *ptr, size_t nmenb, size_t size);
void					free(void *addr);
int						mallopt(int param, int value);
void					*malloc_spec(size_t size, t_alloc_opts *opts);
void					*ft_print_memory(const void *addr, size_t size);

#endif
