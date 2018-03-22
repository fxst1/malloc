#include <ftmalloc.h>
#include <string.h>

int		main(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
	size_t	i;

	s1 = malloc(sizeof(char) * 10);
	s2 = malloc(sizeof(char) * 20);
	s3 = malloc(sizeof(char) * 30);
	free(s2);
	s4 = malloc(sizeof(char) * 10);
	show_alloc_mem();
	while (i < 2048 * 52)
	{
		s4[i] = '0';
		i++;
	}
	show_alloc_mem();
	return (0);
	(void)s1;
	(void)s3;
	(void)s4;
	(void)i;
}
