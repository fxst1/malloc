#include <ftmalloc.h>

static t_mcfg					init_mcfg(void)
{
# ifdef NO_MT_SAFE
# else
	static pthread_mutex_t		lock = PTHREAD_MUTEX_INITIALIZER;
# endif
	t_mcfg						dat;

	dat.psize = (size_t)getpagesize();
	dat.areas = NULL;
	dat.arenamax = 0;
	dat.malloc_hook = NULL;
	dat.realloc_hook = NULL;
	dat.free_hook = NULL;
# ifdef NO_MT_SAFE
# else
	dat.lock = lock;
# endif
	dat.opts.prot = PROT_READ | PROT_WRITE | PROT_EXEC;
	dat.opts.flags = MAP_PRIVATE | MAP_ANONYMOUS;
	dat.opts.fd = -1;
	dat.opts.offset = 0;
	return (dat);
}

t_mcfg							*mem_get_data(void)
{
	static int					exist = 0;
	static t_mcfg				cfg;

	if (!exist)
	{
		cfg = init_mcfg();
		exist = 1;
	}

	return (&cfg);
}
