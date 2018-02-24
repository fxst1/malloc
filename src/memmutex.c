#include <ftmalloc.h>
void		mem_lock(t_mcfg *dat)
{
# ifdef NO_MT_SAFE
	(void)dat;
# else
	pthread_mutex_lock(&dat->lock);
# endif
}

void		mem_unlock(t_mcfg *dat)
{
# ifdef NO_MT_SAFE
	(void)dat;
# else
	pthread_mutex_unlock(&dat->lock);
# endif
}
