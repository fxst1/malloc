#ifndef TEST_THREAD_H
# define TEST_THREAD_H
# define _GNU_SOURCE
# define MYDBG_FLAG FTMALLOC_SHOW_AREA | FTMALLOC_SHOW_BLOCK
# define MYDBG_USAGE RUSAGE_SELF
# include <pthread.h>
# include <ftmalloc.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>

typedef struct			s_thread_test
{
	pthread_t			id;
	int					num;
	int					iter;
	char				*argv;
}						t_thread_test;

pthread_mutex_t			g_printmutex = PTHREAD_MUTEX_INITIALIZER;

char					*ft_strcat(char *dst, const char *src);

#endif
