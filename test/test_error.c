/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:58:12 by fjacquem          #+#    #+#             */
/*   Updated: 2018/02/24 20:15:52 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmalloc.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#define ALLOC_S 1

static void			free_test(void *addr)
{
	printf("free(%p)\n", addr);
	free(addr);
}

static void			realloc_test(void *addr, size_t len)
{
	void			*ret;

	printf("realloc(%p, %zu)\n", addr, len);
	ret = realloc(addr, len);
	printf("\t=> %p\n", ret);
	free(ret);
	free(addr);
}

static void			malloc_test(size_t len)
{
	void			*ret;

	printf("malloc(%zu)\n", len);
	ret = malloc(len);
	printf("\t=> %p\n", ret);
	free(ret);
}

int					main(void)
{
	size_t			max;

	max = (size_t)-1;
	printf("MALLOC :\n");
	malloc_test(max);
	malloc_test((size_t)0);
	malloc_test((size_t)UINT_MAX);
	malloc_test((size_t)INT_MAX);
	printf("\nREALLOC :\n");
	realloc_test(NULL, max);
	realloc_test(NULL, (size_t)0);
	realloc_test(NULL, INT_MAX);
	realloc_test(NULL, UINT_MAX);
	realloc_test(malloc((size_t)0), max);
	realloc_test(malloc((size_t)0), (size_t)0);
	realloc_test(malloc(max), max);
	realloc_test(malloc(max), (size_t)0);
	realloc_test(malloc(UINT_MAX), INT_MAX);
	realloc_test(malloc(INT_MAX), UINT_MAX);
	realloc_test((void*)0xDeadBeef, max);
	realloc_test((void*)0xDeadBeef, (size_t)0);
	printf("\nFREE :\n");
	free_test(NULL);
	free_test((void*)0xDeadBeef);
	return (0);
}
