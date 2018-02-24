#define _GNU_SOURCE

#define MYDBG_FLAG FTMALLOC_SHOW_AREA | FTMALLOC_SHOW_BLOCK
#define MYDBG_USAGE RUSAGE_SELF

#include <pthread.h>
#include <ftmalloc.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct				s_thread_test
{
	pthread_t				id;
	int						num;
	int						iter;
	char					*argv;
}							t_thread_test;

pthread_mutex_t				printmutex = PTHREAD_MUTEX_INITIALIZER;

#ifndef	NOFT
static void					printinfo(t_thread_test *t, const char *buf)
{
	write(STDOUT_FILENO, "=", 1);
	write(STDOUT_FILENO, buf, strlen(buf));
	write(STDOUT_FILENO, " ", 1);
	ft_printnum(t->num);
	write(STDOUT_FILENO, " : ", 3);
	write(STDOUT_FILENO, t->argv, strlen(t->argv));
	write(STDOUT_FILENO, " : iteration ", 13);
	ft_printnum(t->iter);
	write(STDOUT_FILENO, "\n", 1);
}
#else
static void					printinfo(t_thread_test *t, const char *buf)
{
	write(STDOUT_FILENO, "=", 1);
	write(STDOUT_FILENO, buf, strlen(buf));
	write(STDOUT_FILENO, " : ", 3);
	write(STDOUT_FILENO, t->argv, strlen(t->argv));
	write(STDOUT_FILENO, " : iteration ", 13);
	write(STDOUT_FILENO, "\n", 1);
}
#endif

static void					*dothread(void *buffer)
{
	t_thread_test			*info;
	char					*s;

	pthread_mutex_lock(&printmutex);
	info = (t_thread_test*)buffer;
	info->iter++;
	info->argv = realloc(info->argv, strlen(info->argv));
	s = info->argv;
	while (*s)
	{
		*s = toupper(*s);
		s++;
	}
	printinfo(info, "Into thread (realloc string)");
#ifndef	NOFT
	show_alloc_dbg(MYDBG_FLAG, MYDBG_USAGE);
#endif
	pthread_mutex_unlock(&printmutex);
	return (buffer);
}

static t_thread_test		*allocthread(size_t num, char *argv)
{
	t_thread_test			*t;

	t = (t_thread_test*)malloc(sizeof(t_thread_test));
	if (!t)
	{
		write(STDERR_FILENO, "Out of memory\n", 14);
		exit(1);
	}
	t->num = num;
	t->iter = 0;
	t->argv = (char*)malloc(strlen(argv) + 1);
	if (!t->argv)
	{
		write(STDERR_FILENO, "Out of memory\n", 14);
		exit(1);
	}
	t->argv[ strlen(argv) ] = 0;
	strcpy(t->argv, argv);
	printinfo(t, "Creating thread");
	pthread_create(&t->id, NULL, dothread, t);
	return (t);
}

int							main(int argc, char **argv)
{
	size_t			i;
	t_thread_test	**tinfo;

	if (argc > 1)
	{
		tinfo = (t_thread_test**)malloc(sizeof(t_thread_test*) * argc);
		i = 1;
		while (argv[i])
		{
			tinfo[i - 1] = allocthread(i, argv[i]);
			i++;
		}
		tinfo[i - 1] = NULL;
		i = 0;
		while (tinfo[i])
		{
			pthread_join(tinfo[i]->id, NULL);
			i++;
		}
		pthread_exit(NULL);		
		i = 0;
		while (tinfo[i])
		{
			free(tinfo[i]->argv);
			free(tinfo[i]);
			i++;
		}
		free(tinfo);
		write(STDOUT_FILENO, "====================\n", 21);
#ifndef	NOFT
		show_alloc_dbg(MYDBG_FLAG, MYDBG_USAGE);
#endif
	}
	return (0);
}
