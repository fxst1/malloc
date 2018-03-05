/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:57:45 by fjacquem          #+#    #+#             */
/*   Updated: 2018/03/04 19:51:32 by fxst1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_thread.h"

static void				printinfo(t_thread_test *t, const char *buf)
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

static void				*dothread(void *buffer)
{
	t_thread_test		*info;
	char				*s;

	pthread_mutex_lock(&g_printmutex);
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
	show_alloc_mem();
	pthread_mutex_unlock(&g_printmutex);
	return (buffer);
}

static t_thread_test	*allocthread(size_t num, char *argv)
{
	t_thread_test		*t;

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
	ft_strcat(t->argv, argv);
	printinfo(t, "Creating thread");
	pthread_create(&t->id, NULL, dothread, t);
	return (t);
}

static t_thread_test	**main_process(int argc, char **argv)
{
	size_t			i;
	t_thread_test	**tinfo;

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
	return (tinfo);
}

int						main(int argc, char **argv)
{
	size_t			i;
	t_thread_test	**tinfo;

	if (argc > 1)
	{
		tinfo = main_process(argc, argv);
		i = 0;
		while (tinfo[i])
		{
			free(tinfo[i]->argv);
			free(tinfo[i]);
			i++;
		}
		free(tinfo);
		write(STDOUT_FILENO, "====================\n", 21);
		show_alloc_mem();
	}
	return (0);
}
